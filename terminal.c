/*
 * terminal.c
 *
 *  Created on: Oct 22, 2022
 *      Author: omar hamdii
 */
#include "terminal.h"

extern ST_terminalData_t terminal_data ;


/****************************************************global_variable*********************************************/

/* variable indicate the state of the card
 * number = 1 -> WRONG_NAME
 * number = 0 -> TERMINAL_OK
 */
uint8_t number_transdate ;


/* variable indicate the state of the card
 * test = 1 -> TERMINAL_OK
 * test = 0 -> EXPIRED_CARD
 */
uint8_t number_cardexpired ;


/* variable indicate the state of the card
 * test = 1 -> TERMINAL_OK
 * test = 0 -> INVALID_AMOUNT
 */
uint8_t number_transamount;

/* variable indicate the state of the card
 * test = 1 -> TERMINAL_OK
 * test = 0 -> INVALID_MAX_AMOUNT
 */
uint8_t number_maxtrans;


/* variable indicate the state of the card
 * test = 1 -> EXCEED_MAX_AMOUNT
 * test = 0 -> TERMINAL_OK
 */
uint8_t number_amountisbelow ;


/* variable indicate the state of the card
 * number = 1 -> INVALID_CARD
 * number = 0 -> TERMINAL_OK
 */
uint8_t number_cardisvalid ;

/**********************************************Function_prototype**************************************************************/

/*
 * Function Description :
 * This function will ask for the transaction date and store it in terminal data..
 */
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
	printf ("Please enter transaction date \n");
	/*Read transection date from the user */
	gets (termData->transactionDate);

	/*Variable that store TransactionDate length*/
	uint8_t size = strlen (termData->transactionDate);
	if ((termData->transactionDate == NULL_PTR) || (termData->transactionDate[2] != '/') || (termData->transactionDate[5] != '/') || (size<10))
	{
		number_transdate = 1;
		/*Wrong transection date*/
		return WRONG_DATE;
	}
	else
	{
		number_transdate =0;
		/*every thing is ok*/
		return TERMINAL_OK ;
	}
}

/**********************************************************************************************************/

/*
 * Function Description :
 * This function compares the card expiry date with the transaction date..
 */
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
	printf ("Tester Name: Omar Hmady\n");
	printf ("Function Name: isCardExpried\n");
	if ((termData->transactionDate[8]*10 + termData->transactionDate[9]) < (cardData->cardExpirationDate[3]*10 + cardData->cardExpirationDate[4]))
	{
		number_cardexpired = 1;
		return TERMINAL_OK ;
	}
	else
	{
		if ((termData->transactionDate[3]*10 + termData->transactionDate[4]) < (cardData->cardExpirationDate[0]*10 + cardData->cardExpirationDate[1]))
		{
			if ((termData->transactionDate[8]*10 + termData->transactionDate[9]) == (cardData->cardExpirationDate[3]*10 + cardData->cardExpirationDate[4]))
			{
				printf ("Input Date %s\n" , termData->transactionDate);
				printf ("Expire Date %s\n" , cardData->cardExpirationDate);
				number_cardexpired = 1;
				return TERMINAL_OK ;
			}
		}
		else
		{
			number_cardexpired = 0;
			return EXPIRED_CARD ;
		}
	}
}

/**********************************************************************************************************************/

/*
 * Function Description :
 * This function asks for the transaction amount and saves it into terminal data.
 */
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
	printf ("Please enter transaction amount \n");
	scanf (" %f" , &termData->transAmount);
	//printf ("%d\n" , termData->transAmount);

	if (termData->transAmount <= 0)
	{
		number_transamount = 0;
		return INVALID_AMOUNT;
	}
	else
	{
		number_transamount =1 ;
		return TERMINAL_OK ;
	}
}

/********************************************************************************************/

/*
 * Function Description :
 * This function takes the maximum allowed amount and stores it into terminal data..
 */
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount)
{
	termData->maxTransAmount=maxAmount ;
	printf ("Input Date %f \n" , termData->maxTransAmount);
	printf ("Expected input bigger than zero and less or equal Max amount\n");
	if (maxAmount <= 0)
	{
		number_maxtrans = 0;
		return INVALID_MAX_AMOUNT ;
	}
	else
	{
		number_maxtrans = 1;
		return TERMINAL_OK ;
	}
}



/*
 * Function Description :
 * This function compares the transaction amount with the terminal max allowed amount.
 */

/******************************************************************************************/

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
	if (termData->maxTransAmount < termData->transAmount)
	{
		number_amountisbelow = 1;
		return EXCEED_MAX_AMOUNT ;
	}
	else
	{
		number_amountisbelow = 0;
		return TERMINAL_OK ;
	}
}



/*
 * Function Description :
 * This function will check if the PAN is a Luhn number or not.
 */
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData) // Optional
{
	/*store size of PAN 16-18*/
	uint8_t size = strlen (cardData->primaryAccountNumber);

	/*
	 * variable store in in summation of even number in the Array primaryAccountNumber
	 */
	uint8_t sum_even = 0;


	/*
	 * variable store in in summation of odd number after multiplying by 2 in the Array primaryAccountNumber
	 */
	uint8_t sum_odd = 0;


	for (uint8_t i =0 ; i<=size ; i=i+2)
	{
		sum_even = sum_even + cardData->primaryAccountNumber[i];
	}

	for (uint8_t i =1 ; i<=size ; i=i+2)
	{
		if ((cardData->primaryAccountNumber[i]*2)>=10)
		{
			sum_odd = sum_odd + (cardData->primaryAccountNumber[i]%10) + 1;
		}
		else
		{
			sum_odd = sum_odd + (cardData->primaryAccountNumber[i]*2);
		}
	}

	if ((sum_even + sum_odd)==100)
	{
		number_cardisvalid = 0;
		return TERMINAL_OK ;
	}
	else
	{
		number_cardisvalid = 1 ;
		return INVALID_CARD ;
	}
}



/************************************************Test_function*************************************************/


/*
 * Function Description :
 * function discripe card state
 * WRONG_DATE or CARD_OK
 */
void getTransactionDateTest(void)
{
	printf ("Tester Name: Omar Hmady\n");
	printf ("Function Name: getTransactionDate\n");
	switch (number_transdate) {
	case 0:
		printf (" TERMINAL_OK\n");
		printf ("\n");
		break;

	case 1:
		printf (" WRONG_DATE\n");
		printf ("\n");
		getTransactionDate (&terminal_data);
		getTransactionDateTest ();
		break;

	default:
		break;
	}
}



/*
 * Function Description :
 * function discripe card state
 * EXPIRED_CARD or TERMINAL_OK
 */
void isCardExpriedTest(void)
{
	switch (number_cardexpired)
	{

	case 0:
		printf ("Expired Card\n");
		printf ("\n");
		break;

	case 1:
		printf ("NOT Expired Card\n");
		printf ("\n");
		break ;

	default:
		break;
	}
}


/*
 * Function Description :
 * function discripe card state
 * INVALID_AMOUNT or TERMINAL_OK
 */
void getTransactionAmountTest(void)
{
	printf ("Tester Name: Omar Hmady\n");
	printf ("Function Name: getTransactionAmount\n");
	switch (number_transamount)
	{
	case 0:
		printf ("INVALID AMOUNT\n");
		printf ("\n");
		getTransactionAmount(&terminal_data);
		getTransactionAmountTest();
		break;

	case 1:
		printf ("VALID AMOUNT\n");
		printf ("\n");
		break;
	default:
		break;
	}
}


/*
 * Function Description :
 * function discripe card state
 * INVALID_AMOUNT or TERMINAL_OK
 */
void setMaxAmountTest(void)
{
	printf ("Tester Name: Omar Hmady\n");
	printf ("Function Name: setMaxAmount\n");
	switch (number_maxtrans) {
	case 0:
		printf ("INVALID ,MAX_AMOUNT\n");
		printf ("\n");
		break;

	case 1:
		printf ("TERMINAL_OK\n");
		printf ("\n");
		break ;
	default:
		break;
	}
}


/*
 * Function Description :
 * function discripe card state
 * EXCEED_MAX_AMOUNT or TERMINAL_OK
 */
void isBelowMaxAmountTest(void)
{
	printf ("Tester Name: Omar Hmady\n");
	printf ("Function Name: isBelowMaxAmount\n");
	switch (number_amountisbelow)
	{

	case 0:
		printf (" TERMINAL_OK\n");
		printf ("\n");
		break;

	case 1:
		printf (" EXCEED_MAX_AMOUNT\n");
		printf ("\n");
		break;
	default:
		break;
	}
}


/*
 * Function Description :
 * function discripe card state
 * INVALID_CARD or TERMINAL_OK
 */
void isValidCardPANTest(void)
{
	printf ("Tester Name: Omar Hmady\n");
	printf ("Function Name: isValidCardPAN\n");
	switch (number_cardisvalid)
	{
	case 0:
		printf (" TERMINAL_OK\n");
		printf ("\n");
		break;

	case 1:
		printf (" INVALID_CARD\n");
		printf ("\n");
		break;
	default:
		break;
	}
}
