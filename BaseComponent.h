//---------------------------------------------------------------------------

#ifndef BaseComponentH
#define BaseComponentH
#include "IMediator.h"
//---------------------------------------------------------------------------
class BaseComponent {
protected:
    IMediator* mediator_;

public:
	BaseComponent(IMediator* mediator = NULL) : mediator_(mediator) {}

	void SetMediator(IMediator* mediator);
};
#endif
