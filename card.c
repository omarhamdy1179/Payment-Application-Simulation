#include "card.h"

extern ST_cardData_t user_data ;


/* variable indicate the state of the card
 * number = 1 -> WRONG_NAME
 * number = 0 -> CARD_OK
 */
uint8_t number_name ;


/* variable indicate the state of the card
 * number = 1 -> WRONG_EXP_DATE
 * number = 0 -> CARD_OK
 */
uint8_t number_expdate ;


/* variable indicate the state of the card
 * number = 1 -> WRONG_PAN
 * number = 0 -> CARD_OK
 */
uint8_t number_pan ;


/*
 * Function Description :
 * This function will ask for the cardholder's name and store it into card data.
 */
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	printf ("Please Enter your Card Name\n");
	gets (cardData->cardHolderName);

	/*Variable that store card name length*/
	uint8_t size = strlen (cardData->cardHolderName);

	if ((size<20) || (size >24) || (cardData->cardHolderName == NULL_PTR))
	{
		/*user enter wrong name*/
		number_name = 1;
		return WRONG_NAME ;
	}
	else
	{
		number_name = 0;
		return CARD_OK ;
	}
}



/*
 * Function Description :
 * This function will ask for the card expiry date and store it in card data.
 */

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	printf ("please enter card expiry date \n");
	gets (cardData->cardExpirationDate);

	/*
	 * Variable that store card name length
	 */
	uint8_t size = strlen (cardData->cardExpirationDate);

	if ((size>5) || (cardData->cardExpirationDate == NULL_PTR) || (cardData->cardExpirationDate[2] != '/') || (size>5))
	{
		/*user enter wrong EXP_DATA*/
		number_expdate = 1;
		return WRONG_EXP_DATE;
	}
	else
	{
		/*Card is ok*/
		number_expdate = 0;
		return CARD_OK ;
	}
}



/*
 * Function Description :
 * This function will ask for the card's Primary Account Number and store it in card data.
 */

EN_cardError_t getCardPAN (ST_cardData_t* cardData)
{
	printf ("Please Enter your Pan number\n");
	gets (cardData->primaryAccountNumber);

	/*
	 * Variable that store card name length
	 */
	uint8_t size = strlen (cardData->primaryAccountNumber);

	if ((cardData->primaryAccountNumber == NULL_PTR) || (size >19) || (size <16))
	{
		number_pan = 1;
		return WRONG_PAN;
	}
	else
	{
		number_pan = 0 ;
		return CARD_OK ;
	}
}


/*
 * Function Description :
 * function discripe card state
 * WRONG_NAME or CARD_OK
 */

void getCardHolderNameTest (void)
{
	printf ("Tester Name: Omar Hmady\n");
	printf ("Function Name: getCardHolderName\n");
	switch (number_name) {
	case 0:
		printf ("CARD_OK\n");
		printf ("\n");
		break;

	case 1:
		printf ("WRONG_NAME\n");
		printf ("\n");
		getCardHolderName(&user_data);
		getCardHolderNameTest ();
		break;


	default:
		break;
	}
}


/*
 * Function Description :
 * function discripe card state
 * WRONG_EXP_DATE or CARD_OK
 */
void getCardExpiryDateTest (void)
{
	printf ("Tester Name: Omar Hmady\n");
	printf ("Function Name: getCardExpiryDate\n");
	switch (number_expdate)
	{
	case 0:
		printf ("CARD_OK\n");
		printf ("\n");
		break;

	case 1:
		printf ("WRONG_EXP_DATE\n");
		printf ("\n");
		getCardExpiryDate(&user_data);
		getCardExpiryDateTest ();
		break;


	default:
		break;
	}

}


/*
 * Function Description :
 * function discripe card state
 * WRONG_PAN or CARD_OK
 */

void getCardPANTest (void)
{
	printf ("Tester Name: Omar Hmady\n");
	printf ("Function Name: getCardPAN\n");
	switch (number_pan)
	{
	case 0:
		printf ("CARD_OK\n");
		printf ("  \n");
		break;

	case 1:
		printf ("WRONG_PAN\n");
		printf (" \n");
		getCardPAN(&user_data);
		getCardPANTest ();
		break;


	default:
		break;
	}
}

