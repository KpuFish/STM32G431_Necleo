#include "main.h"
#include "common.h"
#include "xmodem.h"
#include "ymodem.h"
#include "flash_if.h"
#include "stdint.h"
#include "string.h"


/* 1K Xmodem  */
uint8_t  guint8_tPacketNumber;
uint32_t guint32_tPacketSize;
uint32_t guint32_tPacketTSize;
uint32_t guint32_tXmodem_Size;



void Xmodem_InitVariable(void)
{
    /* 1K  */
    guint8_tPacketNumber  = 0;
    guint32_tPacketSize   = FALSE;
    guint32_tXmodem_Size  = FALSE;

    uart_handle_init();
}

uint8_t Xmodem_Getchar(uint8_t *retChar)
{
    if ((__HAL_UART_GET_FLAG(uart_handler, UART_FLAG_RXNE) ? SET : RESET) == SET)
    {
        *retChar = (uint8_t)uart_handler->Instance->RDR;
    }
    else
    {
        return (FALSE);
    }
    
    return (TRUE);
}

BOOL_e XMODEM_WaitForChar(uint8_t *uint8_tCPtr, uint32_t uint32_tProcessTime)
{
    uint32_t     uint32_tThisms;

    ++uint32_tProcessTime;

    uint32_tThisms = uwTick;

    while (uint32_tProcessTime)
    {
        if (Xmodem_Getchar(uint8_tCPtr))
        {
            return (TRUE);
        }

        if (uwTick != uint32_tThisms) {
            --uint32_tProcessTime;
            uint32_tThisms = uwTick;
        }
    }
    return (FALSE);
}

//---------------------------------------------------------------------
// Packet Check -> Packet Inversion Check -> Data 128 or 1024 -> CRC-16
//---------------------------------------------------------------------
BOOL_e XMODEM_GetRecord(uint8_t *uint8_tDestAddress)
{
    uint32_t    uint32_tSize;
    uint16_t    uint16_tCRC_check = 0;
    uint8_t     uint8_tGetChar    = 0;
    BOOL_e      bGetCheck         = FALSE;

#if _BUint32_tBIT_TO_64BIT_
    uint64_t flash_data     = 0;
    uint8_t  byte_buffer[8] = { 0, };
    uint8_t  idx = 0;
#endif

    /* Packet number */
    bGetCheck = XMODEM_WaitForChar(&uint8_tGetChar, DOWNLOAD_TIMEOUT);
    if ( (!bGetCheck) || (uint8_tGetChar != guint8_tPacketNumber) ) {
        #if DBG_LED_MACRO
        // error dbg
        DBG_LED(100);
        #endif
        return (FALSE);
    }

    bGetCheck = XMODEM_WaitForChar(&uint8_tGetChar, DOWNLOAD_TIMEOUT);
    if ( (!bGetCheck) || !(uint8_tGetChar != ~guint8_tPacketNumber) ) {
        #if DBG_LED_MACRO
        // error dbg
        DBG_LED(500);
        #endif
        return (FALSE);
    }
    
    HAL_FLASH_Unlock();

    /* Get data - 128 or 1024 byte */
#if (!_BUint32_tBIT_TO_64BIT_)
    for (uint32_tSize = 0; uint32_tSize < guint32_tPacketSize; ++uint32_tSize) {
        if ( !XMODEM_WaitForChar(&uint8_tGetChar, DOWNLOAD_TIMEOUT) ) {
            return (FALSE);
        }

        /* CRC calculation */
        uint16_tCRC_check = (uint16_tCRC_check << 8) ^ crc16tab[((uint16_tCRC_check >> 8) ^ uint8_tGetChar) & 0x00FF];
        
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, uint8_tDestAddress++, uint8_tGetChar);
    }
#else
    for (uint32_tSize = 0; uint32_tSize < guint32_tPacketSize; ++uint32_tSize) {
        if ( !XMODEM_WaitForChar(&uint8_tGetChar, DOWNLOAD_TIMEOUT) ) {
            return FALSE;
        }
        
        byte_buffer[idx] = uint8_tGetChar;
        
        uint16_tCRC_check = (uint16_tCRC_check << 8) ^ crc16tab[((uint16_tCRC_check >> 8) ^ uint8_tGetChar) & 0x00FF];

        if (idx == 7) {
            idx = 0;
            memcpy((uint64_t *)&flash_data, (uint64_t *)byte_buffer, sizeof(uint64_t));
            HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, (uint32_t)uint8_tDestAddress, flash_data);
            uint8_tDestAddress += sizeof(uint64_t);
            flash_data = 0;
        } else {
            idx++;
        }
    }
#endif

    HAL_FLASH_Lock();
    
    /* high & low CRC bit */
    uint16_tCRC_check &= 0xFFFF;
    bGetCheck = XMODEM_WaitForChar(&uint8_tGetChar, DOWNLOAD_TIMEOUT);
    if ((!bGetCheck) || (uint8_tGetChar != (uint8_t)((uint16_tCRC_check >> 8) & 0xFF)))
    {
        return (FALSE);
    }    

    bGetCheck = XMODEM_WaitForChar(&uint8_tGetChar, DOWNLOAD_TIMEOUT);
    if ((!bGetCheck) || (uint8_tGetChar != (uint8_t)(uint16_tCRC_check & 0xFF)))
    {
        return (FALSE);
    }    

    return (TRUE);
}

 // 128 or 1024 xmodem Rx

BOOL_e XMODEM_Rx(uint32_t *p_size, uint8_t *uint8_tDestAddress)
{
    uint32_t     uint32_tState;
    uint32_t     uint32_tRetrynum = 10;                            
    uint8_t      uint8_tGetChar;
    uint8_t     *uint8_tStartAddress =  uint8_tDestAddress;

    guint32_tPacketTSize = 0;
    guint8_tPacketNumber = 1;
    uint32_tState        = WAITING_START;
    
    while (uint32_tRetrynum) 
    {                              
        if (uint32_tState == WAITING_START)                 
        {
            Serial_PutByte('C');

            if (XMODEM_WaitForChar(&uint8_tGetChar, DOWNLOAD_TIMEOUT))
            {
                /* packet head packet size  */
                if (uint8_tGetChar == XMODEM_SOH)
                {
                    guint32_tPacketSize = PACKET_SIZE_SOH;
                    ChangeState(uint32_tState, RX_PACKET);
                }
                
                // x modem 1024byte
                if (uint8_tGetChar == XMODEM_STX)
                {
                    guint32_tPacketSize = PACKET_SIZE_STX;
                    ChangeState(uint32_tState, RX_PACKET);
                }

                if ((uint8_tGetChar == ABORT1) || (uint8_tGetChar == ABORT2))
                {
                    return (FALSE);
                }
            }
        }

        if (uint32_tState == WAIT_HEAD)                      
        {
            if (!XMODEM_WaitForChar(&uint8_tGetChar, DOWNLOAD_TIMEOUT))     
            {                                           
                Serial_PutByte(XMODEM_NAK);

                uint32_tRetrynum--;                         
            }
            else if (uint8_tGetChar == XMODEM_SOH)
            {
                guint32_tPacketSize = PACKET_SIZE_SOH;
                ChangeState(uint32_tState, RX_PACKET);
            }
            else if (uint8_tGetChar == XMODEM_STX)
            {
                guint32_tPacketSize = PACKET_SIZE_STX;
                ChangeState(uint32_tState, RX_PACKET);
            }
            else if (uint8_tGetChar == XMODEM_EOT) 
            {
                Serial_PutByte(XMODEM_ACK);

                *p_size = (uint8_tDestAddress - uint8_tStartAddress);
                //*p_size = guint32_tPacketTSize;
                return (TRUE);
            }

            if (uint8_tGetChar == XMODEM_CAN) /* CANCEL */
            {
                return (FALSE);                        
            }
        }

        if (uint32_tState == RX_PACKET)
        {
            if (XMODEM_GetRecord(uint8_tDestAddress))
            {
                Serial_PutByte(XMODEM_ACK);
                uint8_tDestAddress += guint32_tPacketSize;
                guint32_tPacketTSize += guint32_tPacketSize;
                ++guint8_tPacketNumber;
                ChangeState(uint32_tState, WAIT_HEAD);
            }
            else
            {
                Serial_PutByte(XMODEM_ACK);
                uint32_tRetrynum--;
                ChangeState(uint32_tState, WAIT_HEAD);
            }
        }
    }

    return (FALSE);
}


/* 1K XMODEM Upload Function */
// Send the 1k packet
BOOL_e XMODEM_SendRecord(uint8_t *uint8_tDataAddress, int32_t int32_tDataLength, uint32_t uint32_tTypeHead)
{
    uint32_t         uint32_tSize;
    uint16_t         uint16_tCRC_check;
    uint8_t          uint8_tCPtr;

    uint16_tCRC_check = 0;

    Serial_PutByte(XMODEM_SOH + uint32_tTypeHead);
    Serial_PutByte(guint8_tPacketNumber);
    Serial_PutByte((uint8_t)~guint8_tPacketNumber);

    for (uint32_tSize = 0; uint32_tSize < guint32_tPacketSize; ++uint32_tSize)
    {
        if (XMODEM_GetRecord(&uint8_tCPtr))
        {
            if (uint8_tCPtr == XMODEM_CAN)   return (FALSE);
        }

        if (int32_tDataLength < uint32_tSize)
        {
            uint16_tCRC_check = (uint16_tCRC_check<<8) ^ crc16tab[((uint16_tCRC_check>>8) ^ 0)&0x00FF];
            Serial_PutByte(0);
        }
        else
        {
            uint16_tCRC_check = (uint16_tCRC_check<<8) ^ crc16tab[((uint16_tCRC_check>>8) ^ (*uint8_tDataAddress))&0x00FF];
            Serial_PutByte(*uint8_tDataAddress++);
        }
    }

    Serial_PutByte(uint16_tCRC_check>>8);
    Serial_PutByte(uint16_tCRC_check);
    return TRUE;
}


// 1k xmodem Tx
BOOL_e XMODEM_Tx(uint8_t *uint8_tDataAddress, int32_t int32_tDataLength) 
{
    uint32_t     uint32_tState, uint32_tRetrynum=0;
    uint32_t     uint32_tTypeCheck=0, uint32_tTypeHead=1;
    uint8_t      uint8_tGetChar;
    BOOL_e    bCancelCheck;

    guint8_tPacketNumber = 1;
    guint32_tPacketSize = PACKET_SIZE_STX;
    uint32_tState = WAITING_SEND;

    while (1)
    {
        if (uint32_tState == WAITING_SEND)
        {   /* Packet Send start */
            Serial_PutByte('.');
            
            if (XMODEM_WaitForChar(&uint8_tGetChar, DOWNLOAD_TIMEOUT))
            {
                if (uint8_tGetChar == 'C')
                {
                    guint32_tPacketSize = PACKET_SIZE_STX;
                    uint32_tTypeHead=1;
                    ChangeState(uint32_tState, XMODEM_GET_ACK);
                }
            }
        }

        if (uint32_tState == XMODEM_GET_ACK)
        {
            if (int32_tDataLength > 0)
            {
                bCancelCheck = XMODEM_SendRecord(uint8_tDataAddress, int32_tDataLength, uint32_tTypeHead);    /* Send Packet */
                if (!bCancelCheck)  return (FALSE);

                if (XMODEM_WaitForChar(&uint8_tGetChar, DOWNLOAD_TIMEOUT))
                {
                    if (uint8_tGetChar == XMODEM_ACK)    /* Send success */
                    {
                        uint8_tDataAddress += guint32_tPacketSize;
                        int32_tDataLength -= guint32_tPacketSize;
                        ++guint8_tPacketNumber;
                        uint32_tTypeCheck = 0;
                        ChangeState(uint32_tState, XMODEM_GET_ACK);
                    }
                    if (uint8_tGetChar == XMODEM_NAK)    /* Send fail */
                    {
                        uint32_tRetrynum++;
                        uint32_tTypeCheck++;
                        
                        if (uint32_tRetrynum > 10)
                        {
                            Serial_PutByte(XMODEM_CAN);

                            return (FALSE);
                        }
                        
                        if ((uint32_tTypeCheck == 3) && (guint8_tPacketNumber == 1))
                        {
                            guint32_tPacketSize = PACKET_SIZE_SOH;
                            uint32_tTypeHead=0;
                        }

                        ChangeState(uint32_tState, XMODEM_GET_ACK);
                    }
                    
                    if (uint8_tGetChar == XMODEM_CAN)    /* Cancel */
                    {
                        return (FALSE);
                    }
                }
            }
            else
            {
                Serial_PutByte(XMODEM_EOT);          /* End */

                if (XMODEM_WaitForChar(&uint8_tGetChar, DOWNLOAD_TIMEOUT))
                {
                    if (uint8_tGetChar == XMODEM_ACK)
                    {
                        return (TRUE);
                    }

                    if (uint8_tGetChar == XMODEM_CAN)    /* Cancel */
                    {
                        return (FALSE);
                    }
                }
            }
        }
    }
}

