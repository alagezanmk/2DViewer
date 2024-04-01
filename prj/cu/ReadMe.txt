Features to add
	1. CGAttr
		1, Animation Attribute connection support
		2. Inherited Attribute connection support if this is NOT SET type
		3. Event for 
			1. Validation
			2. Update
			3. Changed - Done as per DOM specification

	2. Selection Tool - CGSelectionTool
	3. CGContainer 
		1. m_aRotate  Attribute

	4. CGElement 
		1. m_pUI
		
	5. CGMutationEvent's type
		1. DOMSubTreeModified
		2. DOMNodeInserted
		3. DOMNodeRemoved
		4. DOMNodeRemovedFromDocument
		5. DOMNodeInsertedIntoDocument
		6. DOMAttrModified					- done
		7. DOMCharacterDataModified

	
	5. CGMouseEvent's type
		

done - 6 Change OnMouseMoveForwading method which is used to share mouse move for view, play, edit wnd
	7. Prop box fix: 
		add On select CB
			On Deselect CB
			Change PropList to Prop Tree List

	8. Attibute Event memory leak
	9. Add Event Pending for Attribute event
	10. Find alternative method for Tool Draw's lower and Upper drawing