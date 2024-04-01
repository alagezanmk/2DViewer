#ifndef __G_ELEMENT_PRIV__PH___
#define __G_ELEMENT_PRIV__PH___

class CGIElementPriv : public CGIElement
{
public:
	void SetRootElement( CGIElement* pElement ) {
		m_pRootElement = pElement; }

	void SetViewPortElement( CGIElement* pElement ) 	{
		m_pViewPortElement = pElement; }
};

#endif __G_ELEMENT_PRIV__PH___