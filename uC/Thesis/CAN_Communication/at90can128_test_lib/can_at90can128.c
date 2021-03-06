/* <Type Definitions> */
enum mob_mode {DISABLED, TRANSMIT_DATA, TRANSMIT_REMOTE, RECEIVE_DATA, AUTO_REPLY};	// Message object mode
enum int_mode {NONE, TX, RX, TXRX};	// Interrupt mode
// Message object structure
typedef struct
{	
	uint32_t	id;			// Identifier (29 Bits)
	uint32_t	idm;		// ID-Mask
	uint8_t		length;		// Length of dataframe 
	uint8_t		data[8];	// Dataframe
}
can_message;
/* </Type Definitions> */

/* <Defines> */
#define MOBS_NUM 15		// Number of available MOBs
#define NOMOB   0xff	// Definition of prohibited MOB
/* </Defines> */

/* <Macros> */
#define setbit(ADR,BIT)		(ADR|=(1<<BIT))		// Macro to set a bit
#define clearbit(ADR,BIT)	(ADR&=~(1<<BIT))	// Macro to clear a bit
#define getbit(ADR, BIT)	(ADR & (1<<BIT))	// Macro to get status of a bit
/* </Macros> */

/* <Function declarations> */
/* Return void */
void can_set_baudrate(uint16_t baud);
void can_set_interrupt(uint8_t mode);
void can_select_mob(uint8_t mob);
void can_set_mob_id_mask(uint32_t idm);
void can_set_mob_id(uint32_t id);
void can_set_mob_mode(uint8_t mode);
void can_set_mob_data(uint8_t *data, uint8_t length);
void can_set_mob_interrupt(uint8_t object);
void can_clear_mob_interrupt(uint8_t object);
void can_init(uint16_t baud, uint8_t intmode);
void can_enable_mob(uint8_t object, uint8_t mode, can_message msg);
void can_disable_mob(uint8_t object);
void can_send_data(uint8_t mob, uint8_t *data, uint8_t length);
/* Return int */
uint32_t can_get_mob_id(void);
uint8_t can_get_mob_mode(void);
uint8_t can_get_mob_interrupt(void);
/* Return can_message */
can_message can_get_mob_data(void);
/* </Function declarations> */

/* Set baudrate (1000, 500, 250, 200, 125, 100kbits/s) for cpu clock (16, 12, 8, 6, 4MHz) */
void can_set_baudrate(uint16_t baud)
{
#if F_CPU	== 16000000
	switch(baud)
	{
		case 1000:
			CANBT1		= 0x00;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;
			break;
		case 500:
			CANBT1		= 0x02;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;
			break;
		case 250:
			CANBT1		= 0x06;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;
			break;
		case 200:
			CANBT1		= 0x08;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;
			break;
		case 125:
			CANBT1		= 0x0e;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;
			break;
		case 100:
			CANBT1		= 0x12;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;
			break;
		default:
			break;
	}
#elif F_CPU	== 12000000
	switch(baud)
	{
		case 1000:
			CANBT1		= 0x00;
			CANBT2		= 0x08;
			CANBT3		= 0x25;
			break;
		case 500:
			CANBT1		= 0x02;
			CANBT2		= 0x08;
			CANBT3		= 0x25;
			break;
		case 250:
			CANBT1		= 0x04;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;
			break;
		case 200:
			CANBT1		= 0x04;
			CANBT2		= 0x0e;
			CANBT3		= 0x4b;
			break;
		case 125:
			CANBT1		= 0x0a;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;
			break;
		case 100:
			CANBT1		= 0x0a;
			CANBT2		= 0x0e;
			CANBT3		= 0x4b;
			break;
		default:
			break;
	}
#elif F_CPU	==  8000000
	switch(baud)
	{
		case 1000:
			CANBT1		= 0x00;
			CANBT2		= 0x04;
			CANBT3		= 0x13;
			break;
		case 500:
			CANBT1		= 0x00;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;
			break;
		case 250:
			CANBT1		= 0x02;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;
			break;
		case 200:
			CANBT1		= 0x02;
			CANBT2		= 0x0e;
			CANBT3		= 0x4b;
			break;
		case 125:
			CANBT1		= 0x06;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;
			break;
		case 100:
			CANBT1		= 0x08;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;
			break;
		default:
			break;
	}
#elif F_CPU	==  6000000
	switch(baud)
	{
		case 1000:
			break;
		case 500:
			CANBT1		= 0x00;
			CANBT2		= 0x08;
			CANBT3		= 0x25;
			break;
		case 250:
			CANBT1		= 0x02;
			CANBT2		= 0x08;
			CANBT3		= 0x25;
			break;
		case 200:
			CANBT1		= 0x02;
			CANBT2		= 0x0c;
			CANBT3		= 0x35;
			break;
		case 125:
			CANBT1		= 0x04;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;
			break;
		case 100:
			CANBT1		= 0x04;
			CANBT2		= 0x0e;
			CANBT3		= 0x4b;
			break;
		default:
			break;
	}
#elif F_CPU	==  4000000
	switch(baud)
	{
		case 1000:
			break;
		case 500:
			CANBT1		= 0x00;
			CANBT2		= 0x04;
			CANBT3		= 0x13;
			break;
		case 250:
			CANBT1		= 0x02;
			CANBT2		= 0x04;
			CANBT3		= 0x13;
			break;
		case 200:
			CANBT1		= 0x00;
			CANBT2		= 0x0e;
			CANBT3		= 0x4b;
			break;
		case 125:
			CANBT1		= 0x02;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;
			break;
		case 100:
			CANBT1		= 0x02;
			CANBT2		= 0x0e;
			CANBT3		= 0x4b;
			break;
		default:
			break;
	}
#endif
}
/* Set interrupt mode */
void can_set_interrupt(uint8_t mode)
{
	switch(mode)
	{
		case NONE:
			clearbit(CANGIE, ENIT);
		  	clearbit(CANGIE, ENRX);
			clearbit(CANGIE, ENTX);
			break;
		case TX:
			setbit(CANGIE, ENIT);
		  	clearbit(CANGIE, ENRX);
			setbit(CANGIE, ENTX);
			break;
		case RX:
			setbit(CANGIE, ENIT);
		  	setbit(CANGIE, ENRX);
			clearbit(CANGIE, ENTX);
			break;
		case TXRX:
			setbit(CANGIE, ENIT);
		  	setbit(CANGIE, ENRX);
			setbit(CANGIE, ENTX);
			break;
		default:
			break;
	}
}
/* Select MOB */
void can_select_mob(uint8_t mob)
{
	CANPAGE	= (mob << 4);
}
/* Set ID mask for selected MOB */
void can_set_id_mask(uint32_t idm)
{
	idm	<<= 3;
	CANIDM4 = ((unsigned char) (idm));
	CANIDM4 |= (0x01 << RTRMSK) | (0x01 << IDEMSK);
	CANIDM3 = (unsigned char) (idm >> 8);
	CANIDM2 = (unsigned char) (idm >> 16);
	CANIDM1 = (unsigned char) (idm >> 24);
}
/* Set ID for selected MOB */
void can_set_id(uint32_t id)
{
	id <<= 3;
	id |= (CANIDT4 & 0x07);

	CANIDT4 = (unsigned char) (id);
	CANIDT3 = (unsigned char) (id >> 8);
	CANIDT2 = (unsigned char) (id >> 16);
	CANIDT1 = (unsigned char) (id >> 24);
}
/* Get ID mask for selected MOB */
uint32_t can_get_mob_id(void)
{
	uint32_t id = 0;

	id |= ((uint32_t) CANIDT1) << 24;
	id |= ((uint32_t) CANIDT2) << 16;
	id |= ((uint32_t) CANIDT3) << 8;
	id |= (CANIDT4 & 0xF8);	//last 3 bits are functional bits
	id >>= 3;

	return id;
}
/* Set mode for selected MOB */
void can_set_mob_mode(uint8_t mode)
{
	setbit(CANCDMOB, IDE);

	switch(mode)
	{
		case DISABLED:
			clearbit(CANCDMOB, CONMOB0);
			clearbit(CANCDMOB, CONMOB1);
			clearbit(CANCDMOB,RPLV);
			clearbit(CANIDT4, RTRTAG);
			clearbit(CANIDM4, RTRMSK);
			break;
		case TRANSMIT_DATA:
			setbit(CANCDMOB, CONMOB0);
			clearbit(CANCDMOB, CONMOB1);
			clearbit(CANCDMOB,RPLV);
			clearbit(CANIDT4, RTRTAG);
			break;
		case TRANSMIT_REMOTE:
			clearbit(CANCDMOB, CONMOB1);
			setbit(CANCDMOB, CONMOB0);
			clearbit(CANCDMOB,RPLV);
			setbit(CANIDT4, RTRTAG);
			break;
		case RECEIVE_DATA:
			clearbit(CANCDMOB, CONMOB0);
			setbit(CANCDMOB, CONMOB1);
			clearbit(CANCDMOB,RPLV);
			clearbit(CANIDT4, RTRTAG);
			break;
		case AUTO_REPLY:
			clearbit(CANCDMOB, CONMOB0);
			setbit(CANCDMOB, CONMOB1);
			setbit(CANCDMOB,RPLV);
			setbit(CANIDT4, RTRTAG);
			break;
		default:
			break;
	}
}
/* Get mode for selected MOB */
uint8_t can_get_mob_mode(void)
{
	uint8_t	mode;
	mode = 0;

	if (!getbit(CANCDMOB, CONMOB1) && !getbit(CANCDMOB, CONMOB0))
	{
		mode = DISABLED;
	}
	else if (!getbit(CANCDMOB, CONMOB1) && getbit(CANCDMOB, CONMOB0) && !getbit(CANIDT4, RTRTAG))
	{
		mode = TRANSMIT_DATA;
	}
	else if (!getbit(CANCDMOB, CONMOB1) && getbit(CANCDMOB, CONMOB0) && getbit(CANIDT4, RTRTAG))
	{
		mode = TRANSMIT_REMOTE;
	}
	else if (getbit(CANCDMOB, CONMOB1) && !getbit(CANCDMOB, CONMOB0) && !getbit(CANIDT4, RTRTAG))
	{
		mode = RECEIVE_DATA;
	}else if (getbit(CANCDMOB, CONMOB1) && !getbit(CANCDMOB, CONMOB0) && getbit(CANCDMOB,RPLV) && getbit(CANIDT4, RTRTAG))
	{
		mode = AUTO_REPLY;
	}

	return mode;
}
/* Set data length for selected MOB */
void can_set_mob_data(uint8_t *data, uint8_t length)
{
	uint8_t	i;
	// Set data length
	if (length & (0x01 << 3))
	{
		setbit(CANCDMOB, DLC3);
	}
	else
	{
		clearbit(CANCDMOB, DLC3);
	}
	
	if (length & (0x01 << 2))
	{
		setbit(CANCDMOB, DLC2);
	}
	else
	{
		clearbit(CANCDMOB, DLC2);
	}
	
	if (length & (0x01 << 1))
	{
		setbit(CANCDMOB, DLC1);
	}
	else
	{
		clearbit(CANCDMOB, DLC1);
	}
	
	if (length & (0x01 << 0))
	{
		setbit(CANCDMOB, DLC0);
	}
	else
	{
		clearbit(CANCDMOB, DLC0);
	}
	// Set data
	for (i = 0; i < length; i++)
	{
		CANMSG	= data[i];
	}
}
/* Get data for selected MOB */
can_message can_get_mob_data(void)
{
	uint8_t	i;
	can_message	msg;

	for (i = 0; i < 8; i++)
	{
		msg.data[i]	= CANMSG;
	}

	return msg;
}
/* Set interrupt for given MOB */
void can_set_mob_interrupt(uint8_t object)
{
	if ((object >= 0) && (object <= 7))
	{
		CANIE2 |= (0x01 << object);
	}
	else if ((object >= 8) && (object <= 14))
	{
		CANIE1 |= (0x01 << (object - 8));
	}
}
/* Get MOB which has forced an interrupt */
uint8_t can_get_mob_interrupt(void)
{
	uint8_t mob;
	uint16_t maske;
	
	maske = CANSIT2 | (CANSIT1 << 8);
	// Error if mask equals zero
	if (maske == 0)
	{
		return NOMOB;
	}
	// Right shifting mask, number of shifts equals MOB number
	for (mob = 0; (maske & 0x01) == 0; mob++)
	{
		maske >>= 1;
	}
	//  Error if MOB number not in range
	if (mob > (MOBS_NUM - 1))
	{
		return NOMOB;
	}
	else
	{
		return mob;
	}
}
/* Clear interrupt for given MOB */
void can_clear_mob_interrupt(uint8_t object)
{
	if ((object >= 0) && (object <= 7))
	{
		CANIE2 &= ~(0x01 << object);
	}
	else if ((object >= 8) && (object <= 14))
	{
		CANIE1 &= ~(0x01 << (object - 8));
	}
}
/* Init CAN controller */
void can_init(uint16_t baud, uint8_t intmode)
{
	CANGCON |= (1 << SWRES);			// Force software reset
	can_set_baudrate(125);				// Set baudrate
	can_set_interrupt(intmode);			// Set interrupt mode
	setbit(CANGCON, ENASTB);			// Enable CAN controller
}
/* Enable the given MOB */
void can_enable_mob(uint8_t object, uint8_t mode, can_message msg)
{
	can_select_mob(object);				// Select MOB
	can_set_mob_interrupt(object);		// Set interrupt
	can_set_id_mask(msg.idm);			// Set ID mask
	can_set_id(msg.id);					// Set ID
	switch(mode)
	{
		case AUTO_REPLY:
			can_set_mob_data(msg.data, msg.length);
			break;
		default:
			break;
	}
	can_set_mob_mode(mode);				// Set mode
}
/* Disable the given MOB */
void can_disable_mob(uint8_t object)
{
	can_select_mob(object);				// Select MOB
	can_clear_mob_interrupt(object);	// Clear interrupt
	can_set_mob_mode(DISABLED);			// Set mode
}
/* Send data */
void can_send_data(uint8_t mob, uint8_t *data, uint8_t length)
{
	uint8_t	mode_buffer;
	uint32_t timeout = 1;
	
	can_select_mob(mob);				// Select MOB
	mode_buffer = can_get_mob_mode();	// Save mode
	can_set_mob_data(data, length);		// Set data and length
	can_set_mob_mode(TRANSMIT_DATA);	// Set transmiter mode
	while ((!getbit(CANSTMOB, TXOK))  && (timeout != 0))	// Wait for transmission complete flag or timeout
	{
		timeout++;
	}			
	clearbit(CANSTMOB, TXOK);			// Reset transmission complete flag
	can_set_mob_mode(mode_buffer);		// Recover MOB mode
}
