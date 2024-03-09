//  ����� ����: ���������� �.�., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
#pragma once

#include "common_functions.h"
//#include <stdint.h>



// ������������ ����� ���������
enum EntityBaseType { 
	NONE_FORMULA, // ��������������
	ATOMIC_FORMULA = 1, // ��������� �������
	NEGATIVE_OPERATION = 2, // �������, ���������� ����������� �������� ���������
	QUANTIFIER1_OPERATION = 3, // �������, ���������� ����������� �������� ��������������
	QUANTIFIER2_OPERATION = 4,
	AND_OPERATION = 5,  // �������, ���������� ����������� �������� "�"
	OR_OPERATION = 6,  // �������, ���������� ����������� �������� "���"
	FORMULA_SET = 7,  // ��������� ���������� �������
	BELONGING_PREDICATE = 8, // �������� �������������� �� ������ ��������� ����������
	TUPLE = 9, // ������
	SUBSET = 10,
	REPLACE_VARIABLE = 11,
};

// ������������ ����� ������
enum Formula_Feature {
	NONE_FEATURE,  // ������������
	TRUTH_FEATURE = 1, // ����������
	FALSE_FEATURE = 2, // ��������
	PERFORMED_FEATURE = 3,  // ������������
	ATOMARN_FEATURE = 4
};

// ������������ ����� ���������� �� �������� "���������� ��� ���������"
enum VariableType {
	NONE_VARIABLE,
	VARIABLE = 1, // ����������
	SET = 2 //���������
};


#if defined(LIBXML_TREE_ENABLED) && defined(LIBXML_OUTPUT_ENABLED)
// ��� ����������� ������������ � ������ ������������� ���������� libxml2 ��� ����������/�������� ����� �/�� xml-�����
// ������ �� ���������� ���� ���������� �� ���� ����������
#else
// ���������� libxml �� ������������
// ���������� �������, ������������ ��� ������������
//class CParentLinkItem;
class CVariableItem;  // ��������������� ���������� ������ ��� ������������ ���������-����������
class CFormulaItem;  // ��������������� ���������� ������ ��� ������������ ������, �������������� ������� Formula
class CSetItem;    // ��������������� ���������� ������ ��� ������������ �������� ����������, �������������� ������� FormulaSet
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����� Level, ���������� ���������� �� ������, ������� ����� ��� ��� EntityVariable, ��� � ��� EntityBase;
//
class Level
{
protected:
	tstring level;
public:
	Level() { level = _T("0"); }; // ����������� �� ���������, ����� �������������� ��� ���������� ���� x0 � ��, ������� ������� ���������� �������
	Level(tstring & tstr) {level = tstr;}; 
	// ����������
	~Level() {};

public:
	tstring & GetLevel() { return level;};
	void SetLevel(tstring & tstr) { level = tstr;};
	//   ����� ���������� ��� ������� ������ Level, � ������ ��������������� ������ ���������� true, ����� false 
	bool compare(const Level& l) { if(!level.compare(l.level)) return true; else return false; };

};




/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����� EntityVariable, �������������� ��������-���������� (��� ����������, ��� � ���������
//
class EntityVariable: public Level
{
	VariableType type; // ������ ���������� ��� ����������-���������
	tstring label;  // ������-����������� ���������� (�� ������� ������)
	tstring index;  // ����� �������, ������ ������ ��� ���������� �������
//	tstring ending_part; // ������� � ������ � �����
	tstring redefinition;
	tstring text;  // ����� ���������� (��� � ��������), �������������� � ������������ ������ (� ������)
public:
	// ����������� �� ���������
	EntityVariable() { type = VARIABLE; label = _T("x"); index = _T(""); SetText(); };
	// ����������
	~EntityVariable() {};
	// �����������, ����������� ����������� ����������, ������� � ��� (���������� ��� ���������)
	EntityVariable( const tstring & str, const tstring & index_, VariableType type_) { label = str; index = index_; type = type_; SetText(); };
	// �����������, ����������� ����������� ����������, �������, ������� � ������ � ����� � ��� (���������� ��� ���������)
//	EntityVariable( const tstring & str, const tstring & index_, tstring & ending_part_, VariableType type_) { label = str; index = index_; type = type_; SetText(); ending_part = ending_part_; };
	// �����������, ��������� ����� ��� ������������ ����������
	EntityVariable( const EntityVariable & ev) { type = ev.type; label = ev.label; index = ev.index; SetText(); Level * pl = (Level *)&ev; SetLevel(pl->GetLevel()); redefinition = ev.redefinition; };
#if defined(LIBXML_TREE_ENABLED) && defined(LIBXML_OUTPUT_ENABLED)
	// � ������ ���������� ���������� libxml2
#else
	// ����� ���������� libxml2 �� �����������
	//	����������� ��� ���������� Variable � Formula �� ������������� ������� CVariableItem, CFormulaItem ��� ������������
	EntityVariable(const CVariableItem& vi);
#endif


	// �����, ������������ ��������� �� ����� ����������
	tstring * GetText() { if(redefinition.length() > 0) return &redefinition; else return &text; };
	// �����, ������������ ��������� �� �������������� ����� ����������
	tstring * GetInitialText() { return &text; };
	// ����� ��������� ����� ���������� � ������������ TS-������� 
//	void SetText() { text = label; if(index.length() > 0) text += _T("<Symbol=/low>") + index; text += ending_part; };
	void SetText() 
	{ 
		text = label; 
//		if(index.length() > 0) 
//			text += _T("<Symbol=/low>") + index; 
		for(size_t i = 0; i < index.length(); i++)
		{
			text += _T("<Symbol=/low>");
			text += index.at(i);
		}
	};
	// ����� ��������� ����� ���������� � ������������ TS-������� 
	void SetRedefinition(tstring & new_text) {redefinition = new_text; };
	// ���������� ����� ��������
	tstring & GetRedefinition() { return redefinition; };
	//   ����� ���������� ��� ����������, � ������ ��������������� �����������, ������� � ���� ���������� true, ����� false 
	bool compare(const EntityVariable&);
	// ����� ��������� true, ���� ��������-���������� �������� ���������
	bool isSet() { bool res = false; (type == SET) ? res=true : res = false; return res; };
	// ����� ���������� true, ���� ��������-���������� �������� ������� ����������
	bool isVariable() { bool res; (type == VARIABLE) ? res=true : res=false; return res; };
	// ���������� ������ �� ������ ���������� (��� �������)
	tstring & GetLabel() { return label; };
	// ���������� ������ �� ������ �������
	tstring & GetIndex() { return index; };
	// ���������� ��� ���������� (������� ���������� ��� ��������-���������)
	VariableType GetType() { return type; };
	// operator ==
//	bool operator == (const EntityVariable& ev);

	void SetIndex(tstring & ind) { index = ind; };
	void SetLabel(tstring & lab) { label = lab; };
	void SetType(VariableType type_) { type = type_; };
//	���������� ����������� ��� ���������� EntityVariable
};



bool operator == (EntityVariable& ev1, EntityVariable& ev2);
/*
//
// ����� ��� ������������� ���������� �� ���������� ����������, ������������ ��� �������� ���������� �� �������������� ���������� � ���������
class NamingVariable : public EntityVariable
{
	vector <EntityVariable *> initial_vars;	// �������������� ��������� ����������
	vector <EntityVariable *> replacing_vars;	// ��������� ��������� ���������
public:
	// ����������� �� ���������
//	NamingVariable(void) { SetType(VARIABLE); SetLabel(tstring(_T("x"))); SetIndex(tstring(_T(""))); SetText(); initial_vars = nullptr; replacing_vars = nullptr; };
	// ����������
	~NamingVariable(void);
	// �����������, ��������� ����� ��� ������������ ����������
	NamingVariable( EntityVariable & ev);
	// ������� ���������� ��������� �� ������ ���������� �������������� ��������� ����������
	vector <EntityVariable *> * getInitialVariables() { return &initial_vars; };
	// ������� ���������� ��������� �� ������ ���������� ���������� ��������� ����������
	vector <EntityVariable *> * getReplacingVariables() { return &replacing_vars; };
};
*/
class EntityBase;

typedef tuple<EntityBase*, int> SetGroup; // ����, ���������� ���������� � ������, ����������� ��� ���������� ��������� ����������
// �������� � ���� ������ ������ ��������� �� ������ EntityBase, ���������� ��������� ����������, ����������� � ������ ������ ��� nullptr
// ���� ��� �� ������ ��������� ����������
// ������ ���� �������� ����� �������� � ������, �� 1 �� 4, � 0, ���� ��� �� ��������� ����������


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����� �ntityBase ������������ ��� ����������� ������ �������� dataSubItems, �������� ������� ��� ������� Formula � Set
//
class EntityBase
{
protected:
	vector <EntityVariable *> freeVariables;  // ��������� ����������
	vector <EntityVariable *> linkedVariables;  // ��������� ����������
	tstring description;  // �������� �������
	tstring addons;  // �������������� ��������
	tstring label; // �������� �����������
	tstring text; // ���� , ������������ ��� ��������, ������� � ��������� ����������, ����� �� ����������� ������ ��� 
	EntityBaseType type; // ��� c�������, ���� �� �������� enum EntityBaseType::

	tstring redefined_text; // ���������������� ����� �������, �������� ����������� ��� ���������������
	bool redefined; // ���� ��� �����������, �������� �� �������

	EntityBase * replaced_base; // ������������ ��� ���� REPLACE_VARIABLE, � ��������� ������� nullptr
	EntityVariable * initial_variable; //��������� �� ���������� ����������, � ��������� ������� nullptr. ���������� ����� ������� ��� �������� ������� ������
	EntityVariable * new_variable; //��������� �� ����������, ������� ��������, � ��������� ������� nullptr. ���������� ����� ������� ��� �������� ������� ������
public:
	// ����������� �� ���������
	EntityBase(void);
	// ����������
	~EntityBase(void);

	// ���������� ��������� �� ��������� �������� ���������� ��� ���� ��������
	vector <EntityVariable *> * getFreeVariables() { return &freeVariables; };
	// ���������� ��������� �� ��������� �������� ���������� ��� ���� ��������
	vector <EntityVariable *> * getLinkedVariables() { return &linkedVariables; };
	// ���������� ����� ��������
	tstring & getText() { if(redefined_text.length() > 0) return redefined_text; else return text; };
//	tstring & getText() { return text; };
	// ���������� ��������� �� �������� ��������
	tstring * getDescription() { return &description; };
	// ���������� ��������� �� �������������� �������� 
	tstring * getAddOns() { return &addons; };
	// �������� �����
	void SetText(LPCTSTR lpctstr);	
//	void SetText(LPCTSTR lpctstr) {	tstring tstr = lpctstr; if(text.compare(tstr)) redefined_text = tstr; };
	// �������� ��� �����
//	void SetIRedefinedText(LPCTSTR lpctstr) { redefined_text = lpctstr; };
	// �������� ��������
	void SetDescription(LPCTSTR lpctstr) { description = lpctstr; };
	// �������� �������������� ��������
	void SetAddons(LPCTSTR lpctstr) { addons = lpctstr; };
	// ���������� ��������� �� �����������
	tstring * getLabel() {return &label; };
	// ���������� ��������� �� �����������
//	tstring * getInitialText() { if(redefined_text.length() > 0) return &text; else return &redefined_text; };
	tstring * getInitialText() { return &text; };
	// ���������� ��������� �� �����������
	tstring * getRedefinedText() { return &redefined_text; };
	// ���������� ��� ��������
//	EntityBaseType getRealType() { if((type != FORMULA_SET) && isRedefined()) return ATOMIC_FORMULA; else return type; };
//	EntityBaseType getType() { if( isRedefined()) return ATOMIC_FORMULA; else return type; };
	EntityBaseType getType() { if((type != FORMULA_SET) && isRedefined()) return ATOMIC_FORMULA; else return type; };
	EntityBaseType getReplacedType();
	// ��������� ��� ��������
	void setType( EntityBaseType type_) { type = type_; };
	// ��������, �������� �� �������� ��������
//	bool isFormula() { bool res = false; ( type != FORMULA_SET )? ((type == REPLACE_VARIABLE) && (replaced_base != nullptr) && replaced_base->isFormula() ? res=true : res = true) : res = false; return res; };
	bool isFormula() { return ( (type != FORMULA_SET) && !( (type == REPLACE_VARIABLE) && (replaced_base != nullptr) && replaced_base->isSet() ) ); };
	// ��������, �������� �� �������� ���������� ����������
//	bool isSet() { bool res = false; ( type == FORMULA_SET )? res=true : ((type == REPLACE_VARIABLE) && (replaced_base != nullptr) && replaced_base->isSet() ? res=true : res = false); return res; };
	bool isSet() { bool res = false; ( (type == FORMULA_SET) || ( (type == REPLACE_VARIABLE) && (replaced_base != nullptr) && replaced_base->isSet() ) )? res=true : res = false; return res; };
	bool isSubset() { if( type == SUBSET ) return true; else return false; };
	bool isRedefined() { return redefined; };
	void setRedefined() { redefined = true; };
	void setTemporarilyUnredefined() {redefined = false;};
	// ������������� �������� ��� ��� ���� REPLACE_VARIABLE
	void SetReplacing(EntityBase * base_, EntityVariable * initial_, EntityVariable * new_);

	void setReplacedBase(EntityBase * preplaced) { replaced_base = preplaced;}; 
	EntityBase * getReplacedBase() { return replaced_base;}; 
	EntityVariable * getInitialVariable() { return initial_variable;}; 
	EntityVariable * getNewVariable() { return new_variable; };
	// ����������, �������� �� ������ ������ ������ ������, ����������� � ������ ��������� ����������, ���������� ������ ��������� �� �������������� ��������� 
	// ���������� � ����� �������� � ������, ���� ������ � ������, nullptr � 0, ���� �� ������
	SetGroup isPartOfSetGroup(vector <EntityBase *> * pentities);

};


class Formula;  // ��������������� ���������� ������ ������
class FormulaSet;  // ��������������� ���������� ������ �������� ����������

typedef tuple<Formula*, EntityVariable *> ParentLink; // ����, ��������� �� ������������ ��������� ������ Formula � ��������� �� ��������� ���������� � ��
// ������ ��� ��������� ����������, ������ ��� �������� ������� ��������� ������ Formula, ���� ��������� �� ��������� ���������� ����� nullptr,
// �� ��������� ���������� �� �������������� ��� ���������� ������� �������, ���� �� ���� ������������ ��� ���������, �� ��� ������ �������������� 
// �������� ���� ���� �������� tuple





/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  class Formula, �������������� �������
//
class Formula: public EntityBase
{
//	tstring text; // ���� �������, ������������ ��� ��������, ������� � ��������� ����������, ����� �� ����������� ������ ��� 
	tstring quantifierPrefix;       // �������-������� ��� ���������, ��� ������� ��������� ������������ ��� ���
	FormulaSet * parent_set;	// ��������� �� ������������ ��������� ���������� (��� ���������� ��������������)
//	Formula(const Formula &); // ����������� �����������
private:
	//  ����� ������ ����� ��� ������������
	void SetSubsetText(vector <EntityBase *> * entities);
	//  ����� ������ ����������� ��� ������������
	void SetSubsetLabel(vector <EntityBase *> * entities);

protected:
	Formula_Feature feature;  // ������������, �������� ��� ���������� �������

public:
	vector <ParentLink *> parents;  // ��������� ���������� �� ���������� ���������, �� ������ ������� ������������ �������
	vector <EntityVariable *> possibleVariables; // ��������� ���������� �� ��������� ��� �������� ��������� ����������, ����������� ��������� ��������
	vector <Formula*> possibleFormulas; // ��������� ���������� �� ��������� ������� ��� �������� �������� ����������� "�" ��� "���"

public:
	// ����������� �� ���������
	Formula(void);
	// ����������
	~Formula(void);
#if defined(LIBXML_TREE_ENABLED) && defined(LIBXML_OUTPUT_ENABLED)
#else
	// ���� �� ������������ ���������� libxml2
	// ����������� ���������� ������� Formula �� �������, ������������ �� xml-�����
	Formula(const CFormulaItem& );
#endif

	// ������� ���������� �� ����� ��������� � ���������� ������ �������� ������
	void unsetFreeVariables(vector <EntityVariable *> * unset); 

//  ������ ��� ������ � private � protected ������� ������
	Formula_Feature getFeature() { return feature; };
	void setFeature(Formula_Feature feature_) { feature = feature_; };
	// ���������� �������, ���� �������� ��������� ���� ����������� ������ �� ���� �������� 
	tstring * getQuantifierPrefix() { return &quantifierPrefix; };


// ������� - ������ ��� �������� ����� ������


	//	����� ������������ ��� ���������� ���� ��������� �������� ����������� ���� type � ������ ������
	friend void joinAllFormulas(vector <EntityBase *> * entities, EntityBaseType type);
	//	��������� �������� ����������� ���� type � ������� �������, ���� ��������� �������� ��������, ������ ����� �������,
	//	������ � � ������ ������ entities � ���������� ��������� �� ����� �������, ����� NULL
	friend Formula * joinFormula(vector <EntityBase *> * entities, EntityBaseType type, Formula * first, Formula * second);
	//  ���������� ������� ���� type � ������� ������� �� ���� ��������� ���������� ���������
	void quantifierFormula(vector <EntityBase *> * entities, EntityBaseType type);
	//	����� ������ ��������� ������� �� ���� �����, ���������������� ������ ������ - ����������, � ������ - ���������
	void setAtomFormula(const EntityVariable & ev1, const EntityVariable & ev2);
	//	����� ������ ��������� ������� �� ���� �����, ���������������� ������ ������ - ����������, � ������ - ���������, � ��������� � � �����
	//  ���������� true, ���� ������� ��� ������������ �� �� ����������� � ����� � ����� ������� ��������� � �����, ����� false
	bool setAtomFormula(vector <EntityBase *> * entities, const EntityVariable & ev1, const EntityVariable & ev2);
	//  ��������� �������� �������� ���� type � ������� ������� �� ��������� ���������� freeVariable, ���� ��������� �������� ��������, ������ ����� �������,
	//  ������ � � ������ ������ entities � ���������� �� �� ���������, ����� NULL
	Formula* quantifierFormula(vector <EntityBase *> * entities, EntityBaseType type, EntityVariable * freeVariable);
	// ������ �� ������� ������� ����� ������������ ��������, ��� ���������� � �������� � �����
	Formula* quantifierFormula(EntityBaseType type, EntityVariable * freeVariable);
	//  ����� ������������ ��� ���������� �������� ����������� ���� type ������� � �������� �� ������ entities
	friend void quantifierAllFormulas(vector <EntityBase *> * entities, EntityBaseType type);
	//	���������� �������� ��������� �� ���� �������� �� ���������� ������.
	friend void negativeAllFormulas(vector <EntityBase *> * entities);
	// �������� �������, ��������� �������� ��������� ������������� � ������� ������� c ������ ���������
	Formula*  negativeFormula(vector <EntityBase *> * entities);
	// �������� �������, ��������� �������� ��������� ������������� � ������� ������� � ������ ��������� ��� i ������ ����
	Formula*  negativeFormula(vector <EntityBase *> * entities, int i);
	// �������� ��������� �������������, ��� ��������, ��������������, ��� ��� ������� ���������� ����� ��� �������� ��������� ����������
	bool predicateBelonging(vector <EntityBase *> * entities, Formula * parent, FormulaSet * set, tstring * ptvars = nullptr);
	// ���������� ������ ��������� ��������������
	void SetPredicateText(Formula * parent, tstring * ptvars);
	// ������������� ����� ��������� ��������������, ���������� ����� ��� ��������� ����������, �� �������� �������� �������� ��������������
	void SetPredicateText(tstring & set_text);
	//  ����� �������� � ������ ������������ ��������  ��������� ���������� �� ������������
	void SetSubsetText(tstring & set_text);
	// �������� ������������, ��� ��������, ��������������, ��� ��� ������� ���������� ����� ��� �������� ��������� ����������
	bool subset(vector <EntityBase *> * entities, FormulaSet * set, vector <EntityVariable *> * variables);

// ������� - ��������������� �������, ����������� ������

	// ����������, �������� �� ������� ���������
	bool isAtom() { return (type == ATOMIC_FORMULA); };
	// ����������, ��������� �� ������� ����������� �������� ���������
//	bool isNegative() { return (type == NEGATIVE_OPERATION); };
	bool isNegative() { if( isRedefined()) return false; else return (type == NEGATIVE_OPERATION); };
	// ����������, ��������� �� ������� ������������ �������� ������ �� ���� �����
//	bool isQuantifier() { if((type == QUANTIFIER1_OPERATION) || (type == QUANTIFIER2_OPERATION)) return true; return false; };
	bool isQuantifier() { if( isRedefined()) return false; else if((type == QUANTIFIER1_OPERATION) || (type == QUANTIFIER2_OPERATION)) return true; return false; };
	bool isBelongingPredicate() { if( isRedefined()) return false; else if((type == BELONGING_PREDICATE)) return true; return false; };
	// ����������, ��������� �� ������� ����������� �������� ���� "�" ���� "���"
//	bool isUnion() { if((type == AND_OPERATION) || (type == OR_OPERATION)) return true; return false; };
	bool isUnion() { if( isRedefined()) return false; else if((type == AND_OPERATION) || (type == OR_OPERATION)) return true; return false; };
	bool isTuple() {return (type == TUPLE); };

//	friend void proccessOneDetail(vector <Formula *> * formulas, tstring * formulaText, Formula * formula);

	// ��������������� �����, ������������ ��� ���������� ������ ������ �����
	friend void proccessOneDetail(vector <EntityBase *> * entities, tstring * formulaText, ParentLink * parent);
	//	������� ��������� ����� ������� � �������� � EntityBase::text
	void putTextOfFormula(vector <EntityBase *> * entities);
	//  ����� � ����������� �� �������� ���� ��������� �������� operation ����������, ���� �� ��������� ��� �������� �������� �� ������ ������� �������,
	//  ���� ����, �� ���������� ��������� �� ������� ������� � ��������� ���������� possibleVariables (��� ����������� ���������) � possibleFormulas
	//  (��� ����������� "�" ��� "���"). ���� �������� �������� ������ ��� (��, ��� ��������, �� ������ ������� ��� ���������) ������������ nullptr
	Formula * operationCandidate(vector <EntityBase *> * entities, EntityBaseType operation);
	// ������ ������������, ����� �� ������������.. ��� ����?
	void SetLabel();
	// ������ ����������� �������
	void SetLabel(vector <EntityBase *> * entities);
	//  ����� ������ ��������� ���������� ��� ������� ������� � ���������� ��������� �� ����, � ������ ������������� ��������� ����� ��������� 
	//  ���������� nullptr
	FormulaSet * makeFormulaSet(vector <EntityBase *> * entities, vector <EntityVariable *> * variables, EntityVariable * pnaming);
	//	����� ����������,  �������� �� ������� ����� �������� ������� ���������� ������ Formula � ��������� ���������� freeVariable
	//  � ������ ���� freeVariable ����� nullptr ��������, ��� ����� ������ �� �������
	bool inChildOf(Formula * formula, EntityVariable * freeVariable = nullptr);
	//  ����� ����������, �������� �� ��� ������� ������� ��������� ��������� ����������. � ������ �������� ���������� ��������� �� ������� �������,
	// ���� ���������� (��� ���������) - ���������� nullptr
	Formula * formulasetCandidate(vector <EntityBase *> * entities);
	//	���������� ����������� ��� ���������� Formula 
//	Formula::Formula(const Formula& fi);

	int getNumberOfParents(bool ignoreRedefined = false);
	ParentLink * getParentLink(int n, bool ignoreRedefined = false) { if(ignoreRedefined || !isRedefined()) return parents.at(n);  else return nullptr; };

	// ���������� ������������ ��������� ���������� ��� ���������� �������������� (nullptr � ���� �������, �� ������ ���������)
	FormulaSet * getParentSet() { return parent_set; };
	// ���������� ������������ ��������� ���������� ��� ���������� �������������� (nullptr � ���� �������, �� ������ ���������)
	void setParentSet(FormulaSet * fs) { parent_set = fs; };
	//	friend bool operator == (const Formula &);
};



/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  class FormulaSet, �������������� ��������� ���������� ��� ������
//
class FormulaSet : public EntityBase //, public Level
{
	// ��������� �� �������-��������
	Formula * formula;
	// ��� ��������� �� ���������-�������� ��� �����������
	FormulaSet * set;
	// ��������� �������, �� ������� �������� ��������� ����������, ��������� ����������
	vector <EntityVariable * > baseVariables;
//	vector <ParentLink *> parents;  // ��������� ���������� �� ���������� ��������� � ��������� ����������, �� ������ ������� ������������ ���������
	// ����������� �������� ����������
	EntityVariable * pnaming;
//	NamingVariable * pnaming;


public:
	// ����������� �� ���������
	FormulaSet(void);
	// ����������
	~FormulaSet(void);
	// ����������� ��� ���������� ��������� ���������� �� ��������� �� ������������ ������� � ��������� ������������ ��������� ���������� (�������)
//	FormulaSet(Formula * parent, vector <EntityVariable *> * variables, EntityVariable & naming_);
	FormulaSet(Formula * parent, vector <EntityVariable *> * variables, EntityVariable * naming_);
#if defined(LIBXML_TREE_ENABLED) && defined(LIBXML_OUTPUT_ENABLED)
#else
	// ���� �� ������������ ���������� libxml2
	// ����������� ���������� ������� Formula �� �������, ������������ �� xml-�����
	FormulaSet(const CSetItem& );  
//	���������� ����������� ��� ���������� FormulaSet
//	FormulaSet::FormulaSet(const FormulaSet& si);
#endif


	//  ����� ��������� ����� ��������� ����������
	void setText();
	//  ����� ��������� ����� ��������� ���������� ��� ������� ������������� ������ ��� ����������
	void setText(tstring tvars);
	//  ����� ��������� ����� ������������ ����������
	void setText(vector <EntityBase *> * entities);
	// ���������� ��������� �� ������, �������������� �������-��������
	Formula * getParentFormula() { return formula; };
	// ������������� �������-��������
	void setParentFormula(Formula * parent) { formula = parent; };
	//  ����� ������ ����������� ��� ��������� ����������
	void SetLabel(vector <EntityBase *> * entities);
	//  ���������� ��� ��������� ���������� ��������� ��� ������ ������ ��������� ���������� - ����������
	bool isVariableBased();  
	// ���������� ��� ��������� ���������� ��������� ��� ������ ��������� ���������� - ��������
	bool isSetBased();
	// ���������� ��������� �� ��������� �������, �� ������� �������� ��������� ����������, ��������� ����������
	vector <EntityVariable *> * getBaseVariables() { return &baseVariables; };
	// ���������� ��������� �� ���������� � ������������ 
	EntityVariable * getNaming() { return pnaming; };
//	NamingVariable * getNaming() { return pnaming; };
	void setNaming(EntityVariable * pev) { pnaming = pev; };
//	void setNaming(NamingVariable * pev) { pnaming = pev; };
//	bool isMixed(); // ���������� ��� ��������� ���������� ��������� ��� ������ ���������� ������� ����������: ���������� � ��������

	// ��������� ���������� �������� ����������, �� ����������� ������, ����� ��� �������� ��� �������� � � ��� � ��� ������� ���� �� ���������� � 
	// ���� ��������� - �������� ��������������. ������� ���������� true, ���� � ������ ������ ��� ����������
	bool isExclusion(Formula * parent);
	// ��������� ���������� �������� ����������, �� ����������� ������, ����� ��� �������� ��� �������� � � ��� � ��� ������� ���� �� ���������� � 
	// ���� ��������� - �������� ��������������. ������� ��������� ������� � ��������� ����������, ������� ����������� � ����� �������
	void proccessExclusion(Formula * parent, vector <EntityVariable *> * variables, tstring & tvars, tstring & tlevel, bool produceText = TRUE);

};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  class Tuple, �������������� �������
//
class Tuple: public Formula
{
private:
public:
	int level;
	// ����������� �� ���������
	Tuple(void);
	Tuple(EntityVariable & ev1, EntityVariable & set);
	Tuple(EntityVariable & ev1, EntityVariable & ev2, EntityVariable & set);
	Tuple(vector <EntityVariable *> * pev, EntityVariable & set);
	Tuple(const CFormulaItem& fi);

	// ����������
	~Tuple(void);

	void SetLevel(int l) { level = l; };
	// ����� ����� �������
	void SetTupleText(vector <EntityVariable *> * depending = nullptr, tstring * ptvars = nullptr);
	// ��� �������� ������ ������� ��������� ��������
	void SetTupleText(tstring & tstr) { text = tstr; };
	void SetTupleLabel(tstring & tstr) { label = tstr; };
//	void putTextOfTuple();
//	void setLabelOfTuple(vector <EntityBase *> * entities);
	//   ����� ���������� ��� ����������, � ������ ��������������� �����������, ������� � ���� ���������� true, ����� false 
	bool compare(const EntityVariable&);
};

// ������� ��������� ���� �������� EntityVariable ��� �������� ��������� �� ���. ������������ � binary_search
bool myentity_compare(EntityVariable * ev, EntityVariable * evcomp);

// ������� ���� � �����, ����������� �� ���������� c ����� ������������ � ��������, ��������� true, ���� �������
bool isExistVariable(tstring & symbol, tstring & index, vector <EntityBase *> * entities);
// ������� ���� � �����, ����������� �� �������������� ��������� ���������� c ����� ������������ � ��������, ��������� true, ���� �������
bool isExistNaming(tstring & symbol, tstring & index, vector <EntityBase *> * entities);
// ������� ���� � �����, ����������� �� �������������� ��������� ���������� c ����� ������������ � ��������, ��������� ��������� �� ����, ���� �������
// � nullptr ���� ����� ��������� ���������� �� �������
FormulaSet * isExistFormulaSet(tstring & symbol, tstring & index, vector <EntityBase *> * entities);

// ������� ���������, �������� �� ������ ��������� ������������ ����� ���������� ��� ��������� � �������������� ������� ������ 
//	(��������, � ������������ ���������)
bool isTextOfVariable(tstring & text);

// ������� ���������� ������ ��������� ����������
tstring makeVarPartOfLabel(vector <EntityBase *> * entities, EntityBase * base);
