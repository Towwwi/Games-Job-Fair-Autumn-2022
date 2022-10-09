// Created by Tommi Kekomäki, all code free to use for educational purposes
#include "GAS/ASCBase.h"
#include "ASCBase.h"


//For broadcasting damage receive between Ability system components
void UASCBase::ReceiveDamage(UASCBase* SourceASC, float UnmitigatedDamage, float MitigatedDamage)
{
		ReceivedDamage.Broadcast(SourceASC, UnmitigatedDamage, MitigatedDamage);
}
