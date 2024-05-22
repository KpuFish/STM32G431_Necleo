
#include "usart.h"
#include "cli_interface.h"
#include "flash_if.h"
#include "xmodem.h"
#include "ymodem.h"



//----------------------------------------
// CHECK . . .
//----------------------------------------

#define BOOT_MODE	0


//----------------------------------------
// UART PRINTF
//----------------------------------------

uint8_t uart_rx_byte = 0;

//----------------------------------------
// retarget
//----------------------------------------
extern UART_HandleTypeDef hlpuart1;
int _write(int32_t file, uint8_t *ptr, int32_t len)
{
    if ( HAL_UART_Transmit(&hlpuart1, ptr, len, len) == HAL_OK ) return len;
    else return 0;
}
//----------------------------------------


//----------------------------------------
// CLI Def
//----------------------------------------
CLI_t cli;


DEBUG_VIEW_t view;

char gRx_cmd_repeat[UART_BUF_MAX] = { 0, };

const CMD_LIST cmd_list[] =
{
    {"?"            , cbf_help             , "Show All Command"                 }, 
    {"RESET"        , cbf_reset            , "System Reboot"                    },
    {"MODEL?"       , cbf_boot_logo        , "Check Model Info"                 },
    {"SN?"          , cbf_sn               , "Check SN Info"                    },
    {"TEST"         , cbf_test             , "Test CLI Arguments"               },
    {"X"            , cbf_xmodem           , "F/W Download using x-modem"       },
    {"Y"            , cbf_ymodem           , "F/W Download using y-modem"       },
    {"DUMP"         , cbf_dump             , "Dump Memory"                      },
    {"FLASH_TEST"   , cbf_flash_test       , "Test Flash WR"                    },
#if BOOT_MODE
    {"JUMP"         , cbf_app_fw_jump      , "Jump from Bootloader to Main App" },
#endif
    {"TAG"          , cbf_tag              , "Check Tag Info"                   },
    {"ASSERT"       , cbf_test_assert      , "Test Assert"                      },
#if LEGACY
    {"EVENT?"       , cbf_event_print      , "Print Event Log"                  },
    {"EVENT_TEST"   , cbf_event_test       , "Test Event Log"                   },
    {"EVENT_RESET"  , cbf_event_reset      , "Reset Event Log"                  },
    {"DBG"          , cbf_dbg_view         , "View Dbg Message"                 },
#endif
#if _USE_AD9833_
    {"WAVE"         , cbf_ad9888_test      , "AD9833 Waveform Test"             },
#endif
    {(char*)NULL    , (CBF)NULL            , (char*)NULL                        }
};


//----------------------------------------
// CLI UART CALLBACK for stm32f
//----------------------------------------
/* USER CODE BEGIN 1 */
void Convert_Char(uint8_t *byte)
{
    #if 1 // LOW to UP
    if ((*byte >= LOWER_A) && (*byte <= LOWER_Z)) {
        *byte -= CONVERT_CHAR_OFFSET;
    }
    #else
    if ((*byte >= UPPER_A) && (*byte <= UPPER_Z)) {
        *byte += CONVERT_CHAR_OFFSET;
    }
    #endif
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == LPUART1) {
        if (uart_rx_byte == ASCII_LF || uart_rx_byte == ASCII_CR || uart_rx_byte == ASTERISK) {
            cli.rx_done  = CLI_READY;
        } else if (uart_rx_byte == ASCII_BACKSPACE || uart_rx_byte == ASCII_DEL) {
            if (cli.rx_index > 0) {
                cli.buffer[--cli.rx_index] = 0;
                printf("%c %c", ASCII_BACKSPACE, ASCII_BACKSPACE);
            }
        } else {
            Convert_Char(&uart_rx_byte);
            cli.buffer[cli.rx_index] = uart_rx_byte;
            cli.rx_index = (cli.rx_index + 1) % UART_BUF_MAX;
        }
        // uart rxne pending clear
        HAL_UART_Receive_IT(&hlpuart1, &uart_rx_byte, UART_BYTE);
    }
}
//----------------------------------------


void CLI_Init(void)
{
    setbuf(stdin, NULL);
    setbuf(stdout,NULL);
    memset(&cli, 0x0, sizeof(CLI_t));
    HAL_UART_Receive_IT(&hlpuart1, &uart_rx_byte, UART_BYTE);
    cbf_boot_logo(0, NULL);
}


/* CLI PARSER */
#define DBG_CMD 0
int parser(char *cmd)
{
    int     argc = 0;
    char   *argv[NUMBER_OF_DELIMITER_VALUE];
    char   **ppStr  = NULL;
    short   str_len = 0;
    
    if (cmd == NULL) {
        printf("CMD Error\r\n");
    }
    
    // is cmd repeat?
    if (uart_rx_byte == ASTERISK) {
        strcpy(cmd, (char *)&gRx_cmd_repeat[0]);
        #if DBG_CMD
        printf("STR:%s", gRx_cmd_repeat);
        #endif
        printf("\r\n");
        cli.is_cmd_repeat = TRUE;
    } else {
        cli.is_cmd_repeat = FALSE;
    }

	//----------------------------------------
    // SPLIT THE UART RX STRING
    //----------------------------------------
    argv[argc++] = strtok(cmd, D_DELIMITER);

    while (1) {
        argv[argc] = strtok(NULL, D_DELIMITER);
        
        if (argv[argc] == NULL) {
            break;
        }

        if (++argc >= NUMBER_OF_DELIMITER_VALUE) {
            break;
        }
    }

    //----------------------------------------
    // FIND THE MATCHED STRING
    //----------------------------------------
    for (short cnt = 0; cmd_list[cnt].name != NULL; cnt++) {
        if (strcmp(cmd_list[cnt].name, argv[0]) == CLI_MATCH) {
            cmd_list[cnt].func(argc, argv);
        }
    }
    
    // Cpy Last Command...
    if (cli.is_cmd_repeat == FALSE) {
        memset((char *)&gRx_cmd_repeat[0], (char)'\0', sizeof(gRx_cmd_repeat));
        ppStr = &argv[0];
        for (short cnt = 0; cnt < argc; cnt++) {
            strcpy(&gRx_cmd_repeat[0] + strlen(&gRx_cmd_repeat[0]), *ppStr++);
            str_len = strlen(&gRx_cmd_repeat[0]);
            gRx_cmd_repeat[str_len] = SPACE_BAR;
        }
        #if DBG_CMD
        printf("cpy str:%s\r\n", gRx_cmd_repeat);
        #endif
    }

    memset(&cli, 0x0, sizeof(CLI_t));
    printf(" $Fish >> ");
    
    return LIST_NOT_FOUND;
}


//----------------------------------------
// CALL BACK FUNCTION
//----------------------------------------
int cbf_boot_logo(int argc, char *argv[])
{
    CONSOLE_SPLIT;
    printf("+==========================================================+\r\n");
    printf("|,------.   ,--.             ,--.                          |\r\n");
    printf("||  .---'   `--'    ,---.    |  ,---.                      |\r\n");
    printf("||  `--,    ,--.   (  .-'    |  .-.  |                     |\r\n");
    printf("||  |`      |  |   .-'  `)   |  | |  |   App V1.0          |\r\n");
    printf("|`--'       `--'   `----'    `--' `--'   %s       |\r\n", __DATE__);
    printf("+==========================================================+\r\n");
    CONSOLE_SPLIT;
    printf(" $Fish >> ");
    return 0;
}

int cbf_sn(int argc, char *argv[])
{
#if LEGACY
    printf("SN : %s\r\n", (char *)tag->fw_sn);
#else
    printf("%s\r\n", __DATE__);
#endif
    return 0;
}

int cbf_help(int argc, char *argv[])
{
    CONSOLE_SPLIT;
    printf("Command List %-6s Description\r\n", "||");
    CONSOLE_SPLIT;
    for (int cnt = 1; cmd_list[cnt].name != NULL; cnt++) {
        printf("%-20s", cmd_list[cnt].name);
        printf("%-30s\r", cmd_list[cnt].description);
    }
    return 0;
}

int cbf_reset(int argc, char *argv[])
{
    // software reset
    HAL_NVIC_SystemReset();
    return 0;
}

int cbf_test(int argc, char *argv[])
{
	printf("argv : %s \r\n", argv[0]);
	//printf("argc : %d , argv : %s \r\n", argc, argv[1]);
	printf("TEST \r\n");    
	return 0;
}


int cbf_xmodem(int argc, char *argv[])
{
#if BOOT_MODE
    uint32_t x_modem_size = 0;
    uint32_t flash_ret    = 0;

    // f/w update using uart polling
    HAL_NVIC_DisableIRQ(LPUART1_IRQn);

    flash_ret = FLASH_If_Erase(APPLICATION_ADDRESS);
    if (flash_ret == FALSE) {
        printf("Flash Erase Error\r\n");
    }

    // entering x-modem ...
    Xmodem_InitVariable();
    
    uint8_t ret = XMODEM_Rx(&x_modem_size, (uint8_t *)APPLICATION_ADDRESS);
    
    HAL_FLASH_Lock();

    printf("\r\n");
    CONSOLE_SPLIT;
    if (ret == FALSE) {
        printf("X-Modem Failed\r\n");
    } else {
        printf("X-Modem Completed size : %u byte\r\n", (int)x_modem_size);
    }
    CONSOLE_SPLIT;

    // resetting uart isr
    HAL_NVIC_SetPriority(LPUART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(LPUART1_IRQn);
#else
    CONSOLE_SPLIT;
    printf("You should update f/w in the boot mode.\r\nboot mode is being entered... \r\n");
    CONSOLE_SPLIT;
#endif
    HAL_NVIC_SystemReset();
    return 0;
}

int cbf_ymodem(int argc, char *argv[])
{
#if BOOT_MODE
    COM_StatusTypeDef result;
    uint32_t Size = 0;
    uint8_t number[11] = { 0, };
    
    Ymodem_InitVariable();

    HAL_NVIC_DisableIRQ(LPUART1_IRQn);

    // entering y-modem ...
    result = Ymodem_Receive(&Size);
    if (result == COM_OK) {
        Serial_PutString((uint8_t *)"\n\n\r Programming Completed Successfully!\n\r--------------------------------\r\n Name: ");
        Serial_PutString((uint8_t *)aFileName);
        Int2Str(number, Size);
        Serial_PutString((uint8_t *)"\n\r Size: ");
        Serial_PutString((uint8_t *)number);
        Serial_PutString((uint8_t *)" Bytes\r\n");
        Serial_PutString((uint8_t *)"-------------------\n");
    } else if (result == COM_LIMIT) {
        Serial_PutString((uint8_t *)"\n\n\rThe image size is higher than the allowed space memory!\n\r");
    } else if (result == COM_DATA) {
        Serial_PutString((uint8_t *)"\n\n\rVerification failed!\n\r");
    } else if (result == COM_ABORT) {
        Serial_PutString((uint8_t *)"\r\n\nAborted by user.\n\r");
    } else {
        Serial_PutString((uint8_t *)"\n\rFailed to receive the file!\n\r");
    }

    // resetting uart isr
    HAL_NVIC_SetPriority(LPUART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(LPUART1_IRQn);
#else
    CONSOLE_SPLIT;
    printf("You should update f/w in the boot mode.\r\nboot mode is being entered... \r\n");
    CONSOLE_SPLIT;
#endif
    HAL_NVIC_SystemReset();
    return 0;
}

static uint8_t check_memory_range(uint32_t address)
{
    if ( ((address >= (uint32_t )FLASH_RANGE_START)        && (address <= (uint32_t )FLASH_RANGE_END)) ||
         ((address >= (uint32_t )ADDR_INTERNAL_SRAM_START) && (address <= (uint32_t )ADDR_INTERNAL_SRAM_END))) {
        return TRUE;
    } else {
        return FALSE;
    }
}

#define LINE				4
#define CHAR_SPACE          ' '
#define CHAR_z              'z'
#define CHAR_dot            '.'
#define ASCII_CHAR_DUMP     0
int cbf_dump(int argc, char *argv[])
{
    uint32_t size  = atoi(argv[2]);
    uint32_t *addr = (uint32_t *) strtol(argv[1], NULL, 16);
    uint32_t is_range_ok = (uint32_t)addr;
    #if ASCII_CHAR_DUMP
    uint8_t buffer[LINE] = { 0, };
    #endif

    if (check_memory_range(is_range_ok) == TRUE) {
        CONSOLE_SPLIT;
        printf("Base Addrr // dump data ... \n");
        CONSOLE_SPLIT;
    } else {
        printf("Command Ex is ""dump [Address] [ReadSize Byte] ->""");
        printf("dump 128 0x08010000\r\n");
        printf("Flash Range is 0x%08lx ~ 0x%08lx\r\n", (long)FLASH_RANGE_START, (long)FLASH_RANGE_END);
        printf("SRAM  Range is 0x%08lx ~ 0x%08lx\r\n", (long)ADDR_INTERNAL_SRAM_START, (long)ADDR_INTERNAL_SRAM_END);
        return FALSE;
    }

    printf("0x%08lx : ", (uint32_t)addr);
    for (uint16_t range = 1; range <= size; range++) {
        #if ASCII_CHAR_DUMP
        if (( *(uint8_t*)addr > CHAR_SPACE) && ( *(uint8_t*)addr <= CHAR_z)) {
            buffer[range - 1] = *(uint8_t*)addr;  
        } else { 
            buffer[range - 1] = CHAR_dot;
        }
        #endif

        printf("%04lx\t",  *(addr++));
        if (range % LINE == 0) {
            #if ASCII_CHAR_DUMP
            printf("\t: %s", buffer);
            #endif
            printf("\r\n");
            printf("0x%08lx : ", (uint32_t)addr);
        }
    }
    printf("\r\n");
    return 0;
}

int cbf_flash_test(int argc, char *argv[])
{
    volatile uint32_t *flash_addr = (volatile uint32_t *) strtol(argv[1], NULL, 16);
    uint32_t addr = (uint32_t)flash_addr;
    uint64_t data = atoi(argv[2]);
    if (check_memory_range(addr) == FALSE) {
        printf("Command is ""flash_test [Address] [Data]\r\n");
        printf("Flash Range is 0x%08lx ~ 0x%08lx\r\n", FLASH_RANGE_START, FLASH_RANGE_END);
        return FALSE;
    }

    printf("Before : Address 0x%08lx : WR Data : 0x%08lx\r\n", (long)addr, (long)data);

    BOOL_e ret = FLASH_If_Erase(addr);
#if 0    
    if (ret != TRUE) {
        printf("Flash Test Error\r\n");
    }
#else
    UNUSED(ret);
#endif

    HAL_FLASH_Unlock();
    ret = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, (uint32_t)flash_addr, (uint64_t)data);
    HAL_FLASH_Lock();

#if 0   
    if (ret != TRUE) {
        printf("Flash Test Error\r\n");
    } 
#endif

    printf("Result : 0x%08lx - 0x%08lx\r\n", (uint32_t)flash_addr, (uint32_t)*flash_addr);
    return 0;
}

#define VCCTOR_TABLE_OFFSET     4
int cbf_app_fw_jump(int argc, char *argv[])
{
    printf("System Start...\r\n");

    __disable_irq();
    
    pFunction Jump_To_Application;

    volatile uint32_t JumpAddress = *(__IO uint32_t*) (APPLICATION_ADDRESS + VCCTOR_TABLE_OFFSET);
    /* Jump to user application */
    Jump_To_Application = (pFunction) JumpAddress;
    /* Initialize user application's Stack Pointer */
    __set_MSP(*(__IO uint32_t*) APPLICATION_ADDRESS);
    Jump_To_Application(); 
    return 0;
}

int cbf_tag(int argc, char *argv[])
{
    CONSOLE_SPLIT;
#if LEGACY
    printf("FW Info\t\t\t%s\r\n", tag->fw_name);
    printf("FW Date\t\t\t%s\r\n", tag->fw_date);
    printf("FW SN\t\t\t%s\r\n", tag->fw_sn );
    printf("FW Version\t\t%s\r\n", tag->fw_version );
    printf("FW Compiled date\t%s\r\n", tag->fw_compile_data);
    printf("FW Compiled time\t%s\r\n", tag->fw_compile_time);
#else
    printf(" S M I L E  ~  :) \r\n");
#endif
    CONSOLE_SPLIT;
    return 0;
}

int cbf_test_assert(int argc, char *argv[])
{
	#if 0
	int ret = atoi(argv[1]);
    assert_param(ret);
	#endif

    //printf("sizeof(uint32_t) %d, sizeof(uint64_t) %d \r\n", sizeof(uint32_t), sizeof(uint64_t));
    return 0;
}

int cbf_event_print(int argc, char *argv[])
{
    #if LEGACY
    PRINT_SRAM_EVENT_LOG();
    #endif
    return 0;
}

int cbf_event_test(int argc, char *argv[])
{
    #if LEGACY
    EVENT_TYPE_e type = atoi(argv[1]);
    if ((type < EVENT_LOG_RESET) || (type >= EVENT_MAX)) {
        return FALSE;
    }

    //printf("type : %d \r\n", type);
    SAVE_SRAM_EVENT_LOG(type);
    #endif
    return 0;
}

int cbf_event_reset(int argc, char *argv[])
{
    #if LEGACY
    RESET_EVENT_LOG();
    #endif
    printf("Event Reset Completed\r\n");
    return 0;
}

int cbf_dbg_view(int argc, char *argv[])
{
    VIEW_DBG_POINT_e view_list[] = 
    {
        VIEW_NONE     ,
        VIEW_DBG_MEASE,
        VIEW_DBG_RELAY,
        VIEW_DBG_ETC  ,
        VIEW_DBG_SRAM ,
        VIEW_DBG_FLASH,
        VIEW_MAX
    };
    
    const uint8_t max_size = sizeof(view_list) / sizeof(view_list[0]);
    long view_point = strtol(argv[1], NULL, 16);
    
    if (view_point <= VIEW_NONE || view_point >= VIEW_MAX) {
        CONSOLE_SPLIT;
        printf("Invalid View Point\r\n");        
        printf("VIEW POINT HEX is ... \r\n");
        CONSOLE_SPLIT;
        for (uint8_t cnt = 1; cnt < max_size - 1; cnt++) {
            printf("0x%08x\r\n", view_list[cnt]);
        }
        CONSOLE_SPLIT;
        return 0;
    }
    
    view.dbg_value = (uint16_t)view_point;

    CONSOLE_SPLIT;
    printf("view_point is 0x%04x\r\n", view.dbg_value);
    CONSOLE_SPLIT;

    return 0;
}

#if _USE_AD9833_
int cbf_ad9888_test(int argc, char *argv[])
{
    uint16_t wave = 0;
    float freq    = 0.0;
    float phase   = 0.0;

    wave = atoi(argv[1]);
    freq = atof(argv[2]);
    phase = atof(argv[2]);

    AD9833_Init(wave, freq, phase);
    AD9833_SetWave(wave);
    AD9833_SetWaveData(freq, phase);
    return 0;
}
#endif
