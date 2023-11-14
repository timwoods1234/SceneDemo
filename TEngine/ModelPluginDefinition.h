#ifndef __MODELPLUGINDEFINITION_H__
#define __MODELPLUGINDEFINITION_H__

#ifndef __TPLUGINDEFINITION_H__
#include "TPluginDefinition.h"
#endif

class ModelPluginDefinition : public TPluginDefinition
{
public:
	ModelPluginDefinition();

	void HandleLoadAttributes(TDynamicSet<TDataVariant>& objects);
	const TString& GetFilename() const;

private:
	TString m_filename;
};

#endif
