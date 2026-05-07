//---------------------------------------------------------------------------

#pragma hdrstop

#include "BaseComponent.h"
//---------------------------------------------------------------------------
void BaseComponent::SetMediator(IMediator* mediator){
		mediator_ = mediator;
}

#pragma package(smart_init)
