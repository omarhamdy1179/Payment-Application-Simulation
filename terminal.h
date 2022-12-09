/*
 * terminal.h
 *
 *  Created on: Oct 22, 2022
 *      Author: omar hamdii
 */

#ifndef TERMINAL_TERMINAL_H_
#define TERMINAL_TERMINAL_H_
#include "../Utalities/stdtypes.h"
#include "../Card/card.h"



/*
 * structure that we store transection data of the client
 * transAmount
 * maxTransAmount
 * transactionDate
 */
typedef struct ST_terminalData_t
{
     float transAmount;
     float maxTransAmount;
     uint8_t transactionDate[11];
}ST_terminalData_t;


/*
 * Enum that indicate the state of the card
 */
typedef enum EN_terminalError_t
{
     TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t ;



/*
 * Function Description :
 * This function will ask for the transaction date and store it in terminal data..
 */
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);



/*
 * Function Description :
 * This function compares the card expiry date with the transaction date..
 */
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData);



/*
 * Function Description :
 * This function asks for the transaction amount and saves it into terminal data.
 */
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);



/*
 * Function Description :
 * This function compares the transaction amount with the terminal max allowed amount.
 */
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);



/*
 * Function Description :
 * This function takes the maximum allowed amount and stores it into terminal data..
 */
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount);



/*
 * Function Description :
 * This function will check if the PAN is a Luhn number or not.
 */
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData); // Optional


void isValidCardPANTest(void) ;

void isBelowMaxAmountTest(void);

void setMaxAmountTest(void);

void getTransactionAmountTest(void);

void isCardExpriedTest(void);

void getTransactionDateTest(void);







#endif /* TERMINAL_TERMINAL_H_ */
