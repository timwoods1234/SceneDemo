#ifndef __TUIMAPPING_H__
#define __TUIMAPPING_H__

#ifndef __TSTRING_H__
#include "TString.h"
#endif

#ifndef __TUIVARIABLEPARAMETER_H__
#include "TUIVariableParameter.h"
#endif

#ifndef __TUIVARIABLERESULT_H__
#include "TUIVariableResult.h"
#endif

class TUIController;

class TUIMapping
{
public:
	TUIMapping();

	virtual ~TUIMapping();

	const TString& GetObjectName() const;

	const TString& GetMappingName() const;

	void SetObjectName(const TString& name);

	void SetMappingName(const TString& name);

	virtual void Execute(const TUIVariableParameter* parameters, TUIVariableResult* result) = 0;

protected:
	TUIController* m_receiver;

	TString m_mappingName;
	TString m_objectName;
};

#endif
