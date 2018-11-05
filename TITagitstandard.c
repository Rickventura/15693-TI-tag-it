/*
 * TITagitstandard.c
 *
 *  Created on: 01-03-2017
 *      Author: Phillip Nash
 * modified by Rickventura for texas 15693 tag-it STANDARD
 */


#include "TITagitstandard.h"
#include "../Codec/ISO15693.h"
#include "../Memory.h"
#include "Crypto1.h"
#include "../Random.h"
#include "ISO15693-A.h"

#define BYTES_PER_PAGE        4
#define MEM_UID_ADDRESS       0x20

static enum {
    STATE_READY,
    STATE_SELECTED,
    STATE_QUIET
} State;


//ISO15693UidType Uid = {0x0, 0x0, 0x0, 0x0, 0x0, 0xC0, 0x07, 0xE0};
//0xE0 = iso15693
//0x07 = TEXAS INSTRUMENTS
//0xC0 0xC1 = "Tagitstandard" 0xC4 or 0xC5 "TagitPro" 0x00 or 0x01 or 0x80 or 0x81 "Tagitplus"

void TITagitstandardAppInit(void)
{
    State = STATE_READY;
}

void TITagitstandardAppReset(void)
{
    State = STATE_READY;
}


void TITagitstandardAppTask(void)
{
    
}

void TITagitstandardAppTick(void)
{

    
}

// void sendIntToTermina(uint8_t val)
// {
//     char buf[16];
//     snprintf(buf,16, "%02x",val);
//     TerminalSendString(buf);
// }

uint16_t TITagitstandardAppProcess(uint8_t* FrameBuf, uint16_t FrameBytes)
{
    
    

    if (FrameBytes >= ISO15693_MIN_FRAME_SIZE) {
        if(ISO15693CheckCRC(FrameBuf, FrameBytes - ISO15693_CRC16_SIZE)) {
            // At this point, we have a valid ISO15693 frame
            uint8_t Command = FrameBuf[1];
            uint16_t ResponseByteCount = ISO15693_APP_NO_RESPONSE;
            uint8_t Uid[8];

	    //MemoryReadBlock(actualTagIt, 0, 44); // read the whole tag from FRAM
            MemoryReadBlock(Uid, MEM_UID_ADDRESS, ActiveConfiguration.UidSize);
	                                      
            //for (j==0 ; j < ActiveConfiguration.UidSize; j++) Uid[j] = actualTagIt[MEM_UID_ADDRESS + j] ;

            switch(State) {
            case STATE_READY:
                if (Command == ISO15693_CMD_INVENTORY) {
                    FrameBuf[0] = 0x00; /* Flags */
                    FrameBuf[1] = 0x00; /* DSFID */		    
                    ISO15693CopyUid(&FrameBuf[2], Uid);
		    
                    ResponseByteCount = 10;
		    

                } else if (Command == ISO15693_CMD_STAY_QUIET) {
                    if (ISO15693Addressed(FrameBuf,Uid)) {
                        State = STATE_QUIET;

                    }

                } else if (Command == ISO15693_CMD_READ_SINGLE) {
		      uint8_t *FramePtr ;	
                      uint8_t PageAddress ;
     	
	
                      if ((FrameBuf[0] & ISO15693_REQ_FLAG_ADDRESS) && ISO15693CompareUid(&FrameBuf[2], Uid) )
			  PageAddress = FrameBuf[10]; // addressed request
		      else
			  PageAddress = FrameBuf[2]; // unaddressed request
			  				      
 		
                      if (FrameBuf[0] & ISO15693_REQ_FLAG_OPTION)
                          {
                              FrameBuf[0] = 0x00; /* Flags */	                      
                              FrameBuf[1] = ( PageAddress == 8 || PageAddress == 9) ? 0x02 : 0x00; /* 0x02 shows factory locked pages 8,9 */	                      
			      FramePtr = FrameBuf + 2;				      
                              ResponseByteCount = 6;

                          } else {
                              FrameBuf[0] = 0x00; /* Flags */			                                    
			      FramePtr = FrameBuf + 1 ;			  
                              ResponseByteCount = 5;
                         }

		       MemoryReadBlock(FramePtr, PageAddress * BYTES_PER_PAGE, BYTES_PER_PAGE);		       

                    }
 
                   
                break;
            case STATE_SELECTED:

                break;

            case STATE_QUIET:
                if (Command == ISO15693_CMD_RESET_TO_READY) {
                    if (ISO15693Addressed(FrameBuf,Uid)) {
                        FrameBuf[0] = 0;
                        ResponseByteCount = 1;
                        State = STATE_READY;
                    }
                }
                break;

            default:
                break;
            }

            if (ResponseByteCount > 0) {
                /* There is data to be sent. Append CRC */
                ISO15693AppendCRC(FrameBuf, ResponseByteCount);
                ResponseByteCount += ISO15693_CRC16_SIZE;
            }

            return ResponseByteCount;
        
        } else { // Invalid CRC
            return ISO15693_APP_NO_RESPONSE;
        }
    } else { // Min frame size not met
        return ISO15693_APP_NO_RESPONSE;
    }
    
}

void TITagitstandardGetUid(ConfigurationUidType Uid)
{
    MemoryReadBlock(&Uid[0], MEM_UID_ADDRESS, ActiveConfiguration.UidSize);
}

void TITagitstandardSetUid(ConfigurationUidType Uid)
{
    MemoryWriteBlock(Uid, MEM_UID_ADDRESS, ActiveConfiguration.UidSize);
}





