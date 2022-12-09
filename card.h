
#include <string.h>
#include <windows.h>
#include <stdio.h>
#include "../Utalities/stdtypes.h"


/*
 * structure that we store data of the client
 * card name
 * account number
 * card expire date
 * primaryAccountNumber
 */


typedef struct ST_cardData_t
{
    uint8_t cardHolderName[25] ;
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
}ST_cardData_t;


/*
 * enum state the case of the card
 */
typedef enum EN_cardError_t
{
    CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;



/*
 * Function Description :
 * This function will ask for the cardholder's name and store it into card data.
 */

EN_cardError_t getCardHolderName(ST_cardData_t* cardData);


/*
 * Function Description :
 * This function will ask for the card expiry date and store it in card data.
 */
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);



/*
 * Function Description :
 * This function will ask for the card's Primary Account Number and store it in card data.
 */

EN_cardError_t getCardPAN(ST_cardData_t* cardData);


void getCardHolderNameTest (void);


void getCardExpiryDateTest (void);



void getCardPANTest (void);

