#ifndef __TUIGRID_H__
#define __TUIGRID_H__

#ifndef __TUIENTITY_H__
#include "TUIEntity.h"
#endif

#ifndef __TVECTOR2_H__
#include "TVector2.h"
#endif

#ifndef __TUIMAPPING_H__
#include "TUIMapping.h"
#endif

class TUIGrid : public TUIEntity
{
public:
	TUIGrid();
	~TUIGrid();

	TXMLObject* HandleLoadElement(const TString& id, TDynamicSet<TDataVariant>& objects);
	void HandleLoadAttributes(TDynamicSet<TDataVariant>& objects);
	void FinaliseLoad();

private:
	void UpdateChildCount();

	TString m_mappingObject;
	TString m_mappingFunction;
	TUIMapping* m_countMapping;

	TUIVariableResult m_variableResult;

	TVector2 m_childSpacing;
};

#endif
