#include "Application.h"


uint8_t name_state ;
uint8_t expiredate_state ;
uint8_t Pan_state ;
uint8_t transdate_state ;
uint8_t expire_state ;
uint8_t transamount_state ;
uint8_t setmax_state;
uint8_t is_below_max_amount_state ;
uint8_t isvalid_account_state ;
uint8_t amount_isavailable ;

uint8_t blocken_acc;
extern ST_accountsDB_t accountsDB[];

ST_cardData_t user_data  ;
ST_terminalData_t terminal_data ;

ST_transaction_t all_data;

void appStart(void)
{

	name_state = getCardHolderName(&all_data.cardHolderData);

	getCardHolderNameTest () ;



	expiredate_state= getCardExpiryDate(&all_data.cardHolderData);
	getCardExpiryDateTest ();


	Pan_state =  getCardPAN(&all_data.cardHolderData);
	getCardPANTest ();



	transdate_state = getTransactionDate (&all_data.terminalData);
	getTransactionDateTest ();


	expire_state = isCardExpired(&all_data.cardHolderData, &all_data.terminalData);
	isCardExpriedTest ();

	if (expire_state== EXPIRED_CARD)
	{
		printf ("Expired card/n");
		return ;
	}
	else
	{


		transamount_state = getTransactionAmount(&all_data.terminalData);
		getTransactionAmountTest();


		setmax_state = setMaxAmount(&all_data.terminalData, 5000);
		setMaxAmountTest ();


		is_below_max_amount_state=isBelowMaxAmount(&all_data.terminalData);
		isBelowMaxAmountTest ();

		if (is_below_max_amount_state == EXCEED_MAX_AMOUNT)
		{
			printf ("Declined amount Exceeding Limit \n");
			return ;
		}
		else
		{

			isvalid_account_state = isValidAccount(&all_data.cardHolderData,  accountsDB);
			isValidAccountTest () ;

			if (isvalid_account_state == ACCOUNT_NOT_FOUND)
			{
				printf ("Declined iNVALID ACCOUNT\n");
				return ;
			}
			else
			{

				blocken_acc =isBlockedAccount(accountsDB);
				isBlockedAccountTest ();

				if (blocken_acc == BLOCKED_ACCOUNT)
				{
					printf ("BLOCKED ACCOUNT/n");
					return ;
				}


				amount_isavailable	= isAmountAvailable(&all_data.terminalData, accountsDB );
				isAmountAvailableTest () ;


				if (amount_isavailable == LOW_BALANCE)
				{
					printf ("Declined insufficient fund\n");
					return ;
				}
				else
				{
					 saveTransaction(&all_data);
					 listSavedTransactions ();

				}
			}
		}

	}

}

