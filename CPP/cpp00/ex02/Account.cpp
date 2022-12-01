#include "Account.hpp"
#include <iostream>
#include <ctime>

int Account::_nbAccounts = -1;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

void	Account::makeDeposit(int deposit)
{
    _displayTimestamp();
    std::cout << "index:" << _accountIndex << ";p_amount:" << _amount;
    Account::_amount += deposit;
    Account::_totalAmount += deposit;
    Account::_nbDeposits++;
    Account::_totalNbDeposits++;
    std::cout << ";deposit:" << deposit;
    std::cout << ";amount:" << _amount << ";nb_deposits:" << _nbDeposits << std::endl;
}

void	Account::_displayTimestamp(void)
{
    time_t	timer;
    char	str[16];

    time(&timer);
    strftime(str, 16, "%Y%m%d_%H%M%S", localtime(&timer));
    std::cout << "[" << str << "] ";
}

void	Account::displayStatus( void ) const
{
    _displayTimestamp();
    std::cout << "index:" << _accountIndex << ";amount:" << _amount << ";deposits:" << _nbDeposits << ";withdrawals:" << _nbWithdrawals << std::endl;
}

bool	Account::makeWithdrawal( int withdrawal )
{
    _displayTimestamp();
    std::cout << "index:" << _accountIndex << ";p_amount:" << _amount;
    if (Account::_amount >= withdrawal)
    {
        std::cout << ";withdrawal:" << withdrawal;
        Account::_amount -= withdrawal;
        Account::_totalAmount -= withdrawal;
        Account::_nbWithdrawals++;
        Account::_totalNbWithdrawals++;
        std::cout << ";amount:" << _amount << ";nb_withdrawals:" << _nbWithdrawals << std::endl;
        return 1;
    }
    else
        std::cout << ";withdrawal:refused" << std::endl;
    return 0;
}

Account::Account(int initial_deposit)
{
    Account::_accountIndex = ++_nbAccounts;
    Account::_amount = initial_deposit;
    Account::_totalAmount += initial_deposit;
    _displayTimestamp();
    std::cout << "index:" << _accountIndex << ";amount:" << _amount << ";created" << std::endl;
}

Account::~Account( void )
{
    _displayTimestamp();
    std::cout << "index:" << _accountIndex << ";amount:" << _amount << ";closed" << std::endl;
}

int	Account::getNbAccounts(void){
    return  _nbAccounts;
}

int	Account::getTotalAmount(void){
    return  _totalAmount;
}

int	Account::getNbDeposits(void){
    return  _totalNbDeposits;
}

int	Account::getNbWithdrawals(void){
    return  _totalNbWithdrawals;
}

void	Account::displayAccountsInfos(void){
    _displayTimestamp();
    std::cout << "accounts:" << getNbAccounts() + 1 << ";total:" << getTotalAmount() << ";deposits:"
        << getNbDeposits() << ";withdrawals:" << getNbWithdrawals() << std::endl;
}




