//  ����� ����: ���������� �.�., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
//#include "StdAfx.h"
#include "Formula.h"
#include "Operation.h"

//TRASNLATED


//
//   ������� ���������� ��� ����������, � ������ ��������������� �����������, ������� � ���� ���������� true, ����� false
//
bool EntityVariable::compare(const EntityVariable& ev)
{
    bool result = false;
//	if((this->label == ev.label ) && ( this->index == ev.index ) && ( this->type == ev.type ))   // ���� ��������� ����������� ����������, ������� � ��� ����������-��������
//		result = true;
    if((!this->label.compare(ev.label) ) && ( !this->index.compare(ev.index) ))   // ���� ��������� ����������� ����������, ������� � ��� ����������-��������
        result = true;
    return result;
}


bool operator == (EntityVariable& ev1, EntityVariable& ev2)
{
    return ev1.compare(ev2);
}

/*
bool EntityVariable::operator==(const EntityVariable& ev)
{
    if( this->compare(ev) )
        return true;
    else
        return false;
}
*/


//
//  ����������� �� ��������� ��� ������ EntityBase
//
EntityBase::EntityBase(void)
{
    redefined = false;
    replaced_base = nullptr;
    initial_variable = nullptr;
    new_variable = nullptr;
}

//
//  ���������� ������ EntityBase
//
EntityBase::~EntityBase(void)
{
    // ������ ��������� ����������
    for(size_t i = 0; i < freeVariables.size(); i++)
        delete freeVariables.at(i);
    for(size_t i = 0; i < linkedVariables.size(); i++)
        delete linkedVariables.at(i);
    if(initial_variable != nullptr)
        delete initial_variable;
    if(new_variable != nullptr)
        delete new_variable;
}


//
//  ����������� �� ���������
//
Formula::Formula(void)
{
//	dobavka=TCHAR(' ');
    type = NONE_FORMULA;
    feature = NONE_FEATURE;
    parent_set = nullptr;
}

/*
Formula::Formula(const Formula &f)
{
    type = f.type;
    text = f.text;
    feature = f.feature;
    description = f.description;
    addons = f.addons;
    label = f.label;
    quantifierPrefix = f.quantifierPrefix;
    parents = f.parents;
    for ( size_t i = 0; i < f.getNumberOfParents(); i++)
    {
        ParentLink * curr = f.getParentLink(i);
        tstring * ptstr1 = get<1>(*curr);
        ParentLink * elem;
        if ( ptstr1 == nullptr )
            elem = new ParentLink(get<0>(*curr), ptstr1);
        else
        {
            tstring * ptstr2 = new tstring(*ptstr1);
            elem = new ParentLink(get<0>(*curr), ptstr2);
        }
        parents.push_back(elem);
    }
    for ( size_t i = 0; i < f.freeVariables.size(); i++)
    {
        tstring * ptstr = f.freeVariables.at(i);
        tstring * ptstr1 = new tstring(*ptstr);
        freeVariables.push_back(ptstr1);
    }
}
*/

//
//  ����������
//
Formula::~Formula(void)
{
    // ������� ��������� ���������� �� ���������� ���������
    for(size_t i = 0; i < getNumberOfParents(); i++)
    {
        EntityVariable * ptstr = get<1>(*(getParentLink(i)));
        if ( ptstr != nullptr )    // ���� ���������� ������� � ������������ �����
            delete ptstr;   // �������� ����������, ��������� � ������������ �����
        delete getParentLink(i);   // �������� ������������ �����
    }
    parents.clear();
    // ������� ��������� ���������� �� ��������� ��� �������� ��������� ����������
    for ( size_t i = 0; i < possibleVariables.size(); i++)
        delete possibleVariables.at(i);    // �������� ��������� ���������� �� ���������� ��������� ���������� ��� ���������� ������
    possibleVariables.clear();
}

//
// ������� ���������� �� ����� ��������� � ���������� ������ �������� ������
//
void Formula::unsetFreeVariables(vector <EntityVariable *> * unset)
{
    // ������� ��������� ���������� �� ��������� ��� �������� ��������� ����������
    for ( size_t i = 0; i < possibleVariables.size(); i++)
        delete possibleVariables.at(i);    // �������� ��������� ���������� �� ���������� ��������� ���������� ��� ���������� ������
    possibleVariables.clear();
    // ���� �� ��������� ���������� �������, ��������� �� ��� � ��������� ���������
    for ( size_t i = 0; i < freeVariables.size(); i++)
    {
        EntityVariable * pev = new EntityVariable(*(freeVariables.at(i)));
        possibleVariables.push_back(pev);    // ��������� ��������� ���������� ���������� ��������� ��������� ����������
    }
    // ������� �� ���������� ���������� "� �������� �� ������ ���������"
    for ( size_t i = 0; i < unset->size(); i++ )
    {
        auto j = possibleVariables.begin();     // ������ ������� � ���������� ���������
        bool found = false;
        EntityVariable * pev1 = unset->at(i);    // ��������� ���������� �� ������ "� ��������"
        // ���� �� ��������� ����������
        for ( ; j != possibleVariables.end(); ++j)
        {
//			EntityVariable * pev2 = j;
            EntityVariable * pev2 = *j;
            if ( ( pev1 != nullptr ) && (*pev1 == *pev2) )    // ���� ������� ����������� ����������
            {
                found = true;
                break;
            }
        }
        if ( found )
        {
            // ������ ���������� �� ������ ���������
            delete(*j);
            possibleVariables.erase(j);
        }
    }
}

//
//	����� ������ ��������� ������� �� ���� �����, ���������������� ������ ������ - ����������, � ������ - ���������, � ��������� � � �����
//
bool Formula::setAtomFormula(vector <EntityBase *> * entities, const EntityVariable & ev1, const EntityVariable & ev2)
{
    feature = ATOMARN_FEATURE;    // "���������"
    type = ATOMIC_FORMULA;    // ��������� ��� - ��������� �������
    // ��������� ��� ��������-����������, ������ - ������� ����������, ������ - ���������
    EntityVariable * pev1 = new EntityVariable(ev1);
    freeVariables.push_back(pev1);
    EntityVariable * pev2 = new EntityVariable(ev2);
    pev2->SetLevel(tstring(_T("<0>")));
    freeVariables.push_back(pev2);
    putTextOfFormula(entities);    // ������ ����� �������
    // ������ ����������� ��� ��������� �������
    label = _T(" P<Symbol=/low>0 ( ");    // ����� "P" � ������ �������� "0", � ���� ��������� ������ ����� �����������, � ����� ������� ������
    // ���� �� ��������� ���������� �������
    for ( size_t i = 0; i < freeVariables.size(); i++ )
    {
        if ( i > 0 )    // ���� ������ ��� ������ �� ����� ����������
            label += _T(" , ");    // ��������� ������� � ������������ ���������
        label += *(freeVariables.at(i)->GetText());    // ��������� ����� ������� ����������
    }
    label += _T(" ) ");    // ��������� ����������� ������ ������� �������
    bool found = false;
    for(auto curr = entities->begin(); curr != entities->end(); curr++)
    {
        EntityBase * pbase = *curr;
        if( pbase->isFormula() )
        {
            Formula * pformula = (Formula *)pbase;
            if( ( pformula->getType() == ATOMIC_FORMULA ) && ( *this == *pformula ) )
                found = true;
        }
    }
    if(!found)
        entities->push_back(this);    // ��������� ������� ������� � ��������� ��������� ����� entities
    return !found;
}


//
//	����� ������ ��������� ������� �� ���� �����, ���������������� ������ ������ - ����������, � ������ - ���������
//
void Formula::setAtomFormula(const EntityVariable & ev1, const EntityVariable & ev2)
{
    feature = PERFORMED_FEATURE;    // "���������"
    type = ATOMIC_FORMULA;    // ��������� ��� - ��������� �������
    // ��������� ��� ��������-����������, ������ - ������� ����������, ������ - ���������
    EntityVariable * pev1 = new EntityVariable(ev1);
    freeVariables.push_back(pev1);
    EntityVariable * pev2 = new EntityVariable(ev2);
    freeVariables.push_back(pev2);
    pev2->SetLevel(tstring(_T("<0>")));
//	putTextOfFormula(entities);    // ������ ����� �������
    // ������ ����������� ��� ��������� �������
    label = _T(" P<Symbol=/low>0 ( ");    // ����� "P" � ������ �������� "0", � ���� ��������� ������ ����� �����������, � ����� ������� ������
    // ���� �� ��������� ���������� �������
    for ( size_t i = 0; i < freeVariables.size(); i++ )
    {
        if ( i > 0 )    // ���� ������ ��� ������ �� ����� ����������
            label += _T(" , ");    // ��������� ������� � ������������ ���������
        label += *(freeVariables.at(i)->GetText());    // ��������� ����� ������� ����������
    }
    label += _T(" ) ");    // ��������� ����������� ������ ������� �������
//	entities->push_back(this);    // ��������� ������� ������� � ��������� ��������� ����� entities
}


//
//	��������� �������� ����������� ���� type � ������� �������, ���� ��������� �������� ��������, ������ ����� �������,
//	������ � � ������ ������ entities � ���������� ��������� �� ����� �������, ����� NULL
//
Formula * joinFormula(vector <EntityBase *> * entities, EntityBaseType type, Formula * first, Formula * second)
{
    Formula * formula = NULL;
    int k = entities->size();
    int t, tt, f, ff;
    bool check, check2;
    if ( ( type == AND_OPERATION ) || ( type == OR_OPERATION ) )
    {
        // ��������, ���������� �� ��� �������� ������� � ����� ��������� � ������ ������������� ���������
        check=true;
        for (t = 0; t < k; t++)
        {
            EntityBase * base = entities->at(t);
            if ( !base->isFormula() )
                continue;
            Formula * curr = (Formula *)base;
            if ( curr->getNumberOfParents() >= 2)
            {
//				if ( (curr->getParentLink(0) == first ) && (curr->getParentLink(1) == second ) && (curr->getType() == type ) )
                if ( (get<0>(*curr->getParentLink(0)) == first ) && (get<0>(*curr->getParentLink(1)) == second ) && (curr->getType() == type ) )
                {
                    check=false;
                    break;
                }
            }
//			if ( (first->getType() == QUANTIFIER1_OPERATION) || (first->getType() == QUANTIFIER2_OPERATION) ||
//					(second->getType() == QUANTIFIER1_OPERATION) || (second->getType() == QUANTIFIER2_OPERATION) )
            if ( first->isQuantifier() || second->isQuantifier() )
            {
                check = false;
                break;
            }
        }
        if (check)	// ���� ��������� �������� ���, ��������
        {
            formula = new Formula();
            formula->setType(type);
            formula->setFeature(PERFORMED_FEATURE);

            Formula * icurr = first;
            Formula * jcurr = second;
//			if ( (icurr->quantifierPrefix.compare(_T(" ")) == 0 ) & ( jcurr->quantifierPrefix.compare(_T(" ")) == 0 ) )  //do kv
            if ( !(icurr->isQuantifier() && jcurr->isQuantifier() ))  //do kv
            {
                if ( (icurr->getFeature() == FALSE_FEATURE) & (type == AND_OPERATION ) )
                    formula->setFeature(FALSE_FEATURE);
                if ( (jcurr->getFeature() == FALSE_FEATURE) & ( type == AND_OPERATION ) )
                    formula->setFeature(FALSE_FEATURE);
                if ( (icurr->getFeature() == FALSE_FEATURE) & ( type == OR_OPERATION  ) )
                    formula->setFeature(TRUTH_FEATURE);
                if ( (jcurr->getFeature() == FALSE_FEATURE) & ( type == OR_OPERATION ) )
                    formula->setFeature(FALSE_FEATURE);
            }
            // ��������� ��������� ���������� �� ������������ ������
            t = icurr->getFreeVariables()->size();
            for (tt = 0; tt < t; tt++)
            {
                EntityVariable * pev = new EntityVariable(*icurr->getFreeVariables()->at(tt));
                formula->getFreeVariables()->push_back(pev);
            }
            f = jcurr->getFreeVariables()->size();
            for (tt = 0; tt < f; tt++)
            {
                check2 = true;
                for (ff = 0; ff < t; ff++)
                {
                    if ( *formula->getFreeVariables()->at(ff) == *jcurr->getFreeVariables()->at(tt) )
//					if ( formula->freeVariables.at(ff)->GetText()->compare(*jcurr->freeVariables.at(tt)->GetText()) == 0 )
                        check2=false;
                }
                if (check2==true)
                {
                    EntityVariable * pev1 = new EntityVariable(*jcurr->getFreeVariables()->at(tt));
                    formula->getFreeVariables()->push_back(pev1);
                }
            }
            ParentLink * elem1 = new ParentLink(icurr, nullptr);
//			formula->parents.push_back(icurr);
            formula->parents.push_back(elem1);
            ParentLink * elem2 = new ParentLink(jcurr, nullptr);
//			formula->parents.push_back(jcurr);
            formula->parents.push_back(elem2);
            formula->putTextOfFormula(entities);
            formula->SetLabel(entities);
        }
    }
    return formula;
}




//
//	����� ������������ ��� ���������� �������� ����������� ���� type ������� � �������� �� ������ entities
//
void joinAllFormulas(vector <EntityBase *> * entities, EntityBaseType type)
{
    int k = entities->size();
    int i, j;
    // ��� ��������� �����, ���� ��������� �� 0 �� (����� ������ - 2), ������ ������ �� ������� ������ �������, �� �� ������ (����� ������ - 1)
    // ������������� ���� ������ (�� �������� ����������) � ��� ��� ��������������� ������� ��������� ������� ���� ����������� ���� type
    // ���� ���������� ��������, �� � newFormula ����� ��������� ���������, ����� ���������� ������� ��������� � entities
    for (i = 0; i < (k - 1); i++)
    {
        EntityBase * first = entities->at(i);
        if ( !first->isFormula() )
            continue;
        for (j = (i + 1); j < k; j++)
        {
            EntityBase * second = entities->at(j);
            if ( !second->isFormula() )
                continue;
            Formula * newFormula = joinFormula(entities, type, (Formula *)first, (Formula *)second );
            if(newFormula)
                entities->push_back(newFormula);
        }
    }
}

//
//  ��������� �������� �������� ���� type � ������� ������� �� ��������� ���������� freeVariable, ���� ��������� �������� ��������, ������ ����� �������,
//  ������ � � ������ ������ entities � ���������� �� �� ���������, ����� NULL
//
Formula* Formula::quantifierFormula(vector <EntityBase *> * entities, EntityBaseType type, EntityVariable * freeVariable)
{
    Formula * formula = NULL;
    int l, j;
    if ( ( type == QUANTIFIER1_OPERATION ) || ( type == QUANTIFIER2_OPERATION ) )    // �������� �� ��� ��������, ������ ���� ����������� ��������
    {
        tstring str = _T(" ");
        Formula * icurr = this;
        // ������ ��������� �� ������ �������� ������
        vector <EntityVariable *> pev_new;
        for(size_t i = 0; i < icurr->freeVariables.size(); i++)
        {
            if(!binary_search(pev_new.begin(), pev_new.end(), icurr->freeVariables.at(i), myentity_compare))
            {
                pev_new.push_back(icurr->freeVariables.at(i));
            }
        }
//		j = icurr->freeVariables.size();
        j = pev_new.size();
        if (j != 0)
        {
            formula = new Formula();    // ������ ����� �������
            for (l = 0; l < j; l++)     // ���� �� ��������� ���������� ������� �������
            {
                if ( !(*pev_new.at(l) == *freeVariable) )    // ���� ��������� ��������� ���������� ����������� � ���, �� ������� ������ �������
                {
//					EntityVariable * newVar = new EntityVariable(*(icurr->freeVariables.at(l)));
                    EntityVariable * newVar = new EntityVariable(*(pev_new.at(l)));
                    formula->freeVariables.push_back(newVar);    // ��������� � � ��������� ���������� ����� �������
                    continue;    // ������� � ��������� ��������� ����������
                }
                // ������ �������� �� ���������� �����������, ������������ � ���, �� ������� �������� ����� �������
                // ��������� ����������� �������� � ������
                if ( type == QUANTIFIER1_OPERATION )
                    str += _T("<Symbol=/34>");
                else
                    str += _T("<Symbol=/36>");

//				str += _T("(") + *(icurr->freeVariables.at(l)->GetText());    // ��������� ����� ������� ������ � ����������� ����������
                str += _T("(") + *(pev_new.at(l)->GetText());    // ��������� ����� ������� ������ � ����������� ����������
                str += _T(")");    // ��������� ������ ������� ������
            }
            // ������ ������������ ����� ��� ����� �������
            EntityVariable * pev = new EntityVariable(*freeVariable);    // ���������� ��� �����
            ParentLink * plcurr = new ParentLink(this, pev);    // ����������, ���� �����
            entities->push_back(formula);    // ��������� ����� ������� � ������ �����
            formula->parents.push_back(plcurr);    // ��������� ������������ ����� � ���������� �������
            formula->quantifierPrefix = str;    // ����� �������
            formula->type = type;     // ����� ��� ��������
            formula->feature = NONE_FEATURE;    // �������������� - � ���� (�������)
            formula->putTextOfFormula(entities);     // ������ ��� ����� �������
            // �������� ����������� ��� ���� �������, ���������� ������������ ��������
            formula->SetLabel(entities);
            // �������� ����������, �� ������� �������� �������, � ������ ��������� ����������
            EntityVariable * plv = new EntityVariable(*freeVariable);
            formula->linkedVariables.push_back(plv);
        }
    }
    return formula;
}

//
// ������ �� ������� ������� ����� ������������ ��������, ��� ���������� � �������� � �����
//
Formula* Formula::quantifierFormula(EntityBaseType type, EntityVariable * freeVariable)
{
    Formula * formula = nullptr;
    int l, j;
    if ( ( type == QUANTIFIER1_OPERATION ) || ( type == QUANTIFIER2_OPERATION ) )    // �������� �� ��� ��������, ������ ���� ����������� ��������
    {
        tstring str = _T(" ");
        Formula * icurr = this;
        j = icurr->freeVariables.size();
        if (j != 0)
        {
            formula = new Formula();    // ������ ����� �������
            for (l = 0; l < j; l++)     // ���� �� ��������� ���������� ������� �������
            {
                if ( !(*freeVariables.at(l) == *freeVariable) )    // ���� ��������� ��������� ���������� ����������� � ���, �� ������� ������ �������
                {
                    EntityVariable * newVar = new EntityVariable(*(icurr->freeVariables.at(l)));
                    formula->freeVariables.push_back(newVar);    // ��������� � � ��������� ���������� ����� �������
                    continue;    // ������� � ��������� ��������� ����������
                }
                // ������ �������� �� ���������� �����������, ������������ � ���, �� ������� �������� ����� �������
                // ��������� ����������� �������� � ������
                if ( type == QUANTIFIER1_OPERATION )
                    str += _T("<Symbol=/34>");
                else
                    str += _T("<Symbol=/36>");

                str += _T("(") + *(icurr->freeVariables.at(l)->GetText());    // ��������� ����� ������� ������ � ����������� ����������
                str += _T(")");    // ��������� ������ ������� ������
            }
            // ������ ������������ ����� ��� ����� �������
            EntityVariable * pev = new EntityVariable(*freeVariable);    // ���������� ��� �����
            ParentLink * plcurr = new ParentLink(this, pev);    // ����������, ���� �����
//			entities->push_back(formula);    // ��������� ����� ������� � ������ �����
            formula->parents.push_back(plcurr);    // ��������� ������������ ����� � ���������� �������
            formula->quantifierPrefix = str;    // ����� �������
            formula->type = type;     // ����� ��� ��������
            formula->feature = NONE_FEATURE;    // �������������� - � ���� (�������)
            // �������� ����������, �� ������� �������� �������, � ������ ��������� ����������
            EntityVariable * plv = new EntityVariable(*freeVariable);
            formula->linkedVariables.push_back(plv);
            // �������� ����������� ��� ���� �������, ���������� ������������ ��������
//    ���� ����� ��������
//			formula->SetLabel(entities);
        }
    }
    return formula;
}




//
//  ���������� ������� ���� type � ������� ������� �� ���� ��������� ���������� ���������
//
void Formula::quantifierFormula(vector <EntityBase *> * entities, EntityBaseType type)
{
    Formula * formula = nullptr;
    int l, j;
    if ( ( type == QUANTIFIER1_OPERATION ) || ( type == QUANTIFIER2_OPERATION ) )     // ��������, ��� ��� �������� ������ ����������� ��������
    {
        tstring str = _T(" ");
        Formula * icurr = this;
        // � ����� �� ��������� ���������� ������� ��������� �������� ����������� �������� �� ��������� ��������� ����������
        j = icurr->freeVariables.size();
        if (j != 0)
        {
            for (l = 0; l < j; l++)
            {
                formula = quantifierFormula(entities, type, freeVariables.at(l));	// ����� �������, �������� ����� ������� ���� ����������� ��������
//				if ( formula != nullptr )
//					formulas->push_back(formula);
            }
        }
    }
//	return formula;
}
//
//  ��������� �������� �������� ���� type � ������ ������
//
void quantifierAllFormulas(vector <EntityBase *> * entities, EntityBaseType type)
{
    tstring str;
    // � ����� ���� �������, ������� � �������� ��������� ����������� �������� �� ���� ��������� ���������� ���������
    for (size_t i = 0; i <entities->size(); i++)
    {
        EntityBase * base = entities->at(i);
        if ( !base->isFormula() )
            continue;
        Formula * icurr = (Formula *)base;
        icurr->quantifierFormula(entities, type);
    }
}

Formula* Formula::negativeFormula(vector <EntityBase *> * entities)
{
    return this->negativeFormula(entities, 0);
}
//
// �������� �������, ��������� �������� ��������� ������������� � ������� �������, ��� i ������ ���� ��� ������ ��������
//
Formula* Formula::negativeFormula(vector <EntityBase *> * entities, int i)
{
    Formula * formula = nullptr;
    Formula * icurr = this;
//	if(icurr->type != NEGATIVE_OPERATION)     // ��������, ��� �������� ������ �������� ���������
//	{
        formula = new Formula();    // ����� �������
        ParentLink * elem = new ParentLink(icurr, nullptr);    // ������ ������������ �����
        formula->parents.push_back(elem);    // ��������� ��� ����� �������
//		formula->parents.push_back(icurr);
        formula->type = NEGATIVE_OPERATION;    // ��� ����� ������� - �������� ���������
        formula->feature = NONE_FEATURE;    // �������������� �������� ��������������

        // ��������� �������������� ����� ������� � ����������� �� �������-��������
        if (icurr->feature == TRUTH_FEATURE)
            formula->feature = FALSE_FEATURE;
        if (icurr->feature == FALSE_FEATURE)
            formula->feature = TRUTH_FEATURE;
        if (icurr->feature == PERFORMED_FEATURE)
            formula->feature = PERFORMED_FEATURE;


        // ���� �� ��������� ���������� �������-��������, ��������� �� ��� � ������ ��������� ���������� ����� �������
        for (size_t t = 0; t < icurr->freeVariables.size(); t++)
        {
            EntityVariable * str = new EntityVariable(*icurr->freeVariables.at(t));
            formula->freeVariables.push_back(str);
        }
        formula->putTextOfFormula(entities);    // ������ ����� �������
        formula->SetLabel(entities);    // �������� ����������� ��� ���� �������, ���������� ���������� �������� ���������
    bool found = false;
    for(auto curr = entities->begin(); curr != entities->end(); curr++)
    {
        EntityBase * pbase = *curr;
        if(i == 0)
        {
            if( pbase->isFormula() )
            {
                Formula * pformula = (Formula *)pbase;
                if( *formula == *pformula )
                {
                    found = true;
                    break;
                }
            }
        }
        else
        {
            if(pbase == (EntityBase *)formula)
            {
                found = true;
                break;
            }
        }
    }
    if(!found)
        entities->push_back(formula);    // ��������� ��������� ������� � ������ ���������
    else
    {
        delete formula;
        formula = nullptr;
    }

    return formula;
}

//
//	���������� �������� ��������� �� ���� �������� �� ���������� ������.
//
void negativeAllFormulas(vector <EntityBase *> * entities)
{
    int k = entities->size();
    for (int i = 0; i < k; i++)
    {
        EntityBase * base = entities->at(i);
        if ( !base->isFormula() )
            continue;
        Formula * icurr = (Formula *)base;
        if (icurr->isNegative())
            continue;
        icurr->negativeFormula(entities);
    }
}


//
//	���������� �������� ��������� �� ���� �������� �� ���������� ������.
//
void proccessOneDetail(vector <EntityBase *> * all_entities, tstring * formulaText, ParentLink* parent)
{

    Formula * ncurr = get<0>(*parent);

    if ( ncurr->isNegative() )
    {
        *formulaText += _T("<Symbol=/216>");
//		*formulaText += _T(" not ");
//		Formula * parent = ncurr->getParentLink(0);
        Formula * parent = get<0>(*ncurr->getParentLink(0));
        tstring prom(parent->getText());
        if ( !parent->isQuantifier() && !parent->isBelongingPredicate() && !parent->isTuple() && !parent->isSubset() && (parent->getType() != REPLACE_VARIABLE))
        {
            if(parent->getRedefinedText()->length() == 0)
                prom = prom.substr(3, prom.length() - 5);
        }
        if(parent->isSubset() || (parent->getType() != REPLACE_VARIABLE))
        {
            *formulaText += _T("(");
        }
        *formulaText += prom;
        if(parent->isSubset() || (parent->getType() != REPLACE_VARIABLE))
        {
            *formulaText += _T(")");
        }
    }
    else
    {
        if(ncurr->getRedefinedText()->length() > 0)
        {
            *formulaText += ncurr->getText();
        }
        else
        {
            if(ncurr->getType() != REPLACE_VARIABLE)
                *formulaText += _T(" ( ");
            if( ncurr->getType() == ATOMIC_FORMULA )
                *formulaText += *(ncurr->getFreeVariables()->at(0)->GetText());
            else if(ncurr->isBelongingPredicate())
            {
                *formulaText += ncurr->getText();
            }
            else if(ncurr->isTuple())
            {
                *formulaText += ncurr->getText();
            }
            else if(ncurr->getType() == REPLACE_VARIABLE)
            {
//				*formulaText += _T("(") + ncurr->getText() + _T(")");
                *formulaText += ncurr->getText();
            }
            else
//				proccessOneDetail(all_formulas,formulaText, ncurr->getParentLink(0));
                proccessOneDetail(all_entities,formulaText, ncurr->getParentLink(0));

//			if ( ncurr->svjazka == TCHAR('0'))
            if ( ncurr->getType() == ATOMIC_FORMULA)
                *formulaText += _T("<Symbol=/0xCE>");
//			*formula += _T(" (- ");
//			else if ( ncurr->svjazka == TCHAR('1')) *formula += _T("<Symbol=/and>");
            else if ( ncurr->getType() == AND_OPERATION)
                *formulaText += _T("<Symbol=/and>");
//			else if ( ncurr->svjazka == TCHAR('2')) *formula += _T("<Symbol=/or>");
            else if ( ncurr->getType() == OR_OPERATION )
                *formulaText += _T("<Symbol=/or>");
//			else if ( ncurr->svjazka == TCHAR('2')) *formula += _T(" v ");

            if( ncurr->getType() == ATOMIC_FORMULA )
                *formulaText += *(ncurr->getFreeVariables()->at(1)->GetText());
            else if(!ncurr->isBelongingPredicate() && !ncurr->isTuple() && !ncurr->isSubset() && (ncurr->getType() != REPLACE_VARIABLE))
//				proccessOneDetail(all_formulas,formulaText, ncurr->getParentLink(1));
                proccessOneDetail(all_entities,formulaText, ncurr->getParentLink(1));
            if(ncurr->getType() != REPLACE_VARIABLE)
                *formulaText += _T(" ) ");
        }
    }
}



//
//	������� ����������,  �������� �� ������� ����� �������� ������� ���������� ������ Formula � ��������� ���������� freeVariable
//  � ������ ���� freeVariable ����� nullptr ��������, ��� ����� ������ �� �������
//
bool Formula::inChildOf(Formula * formula, EntityVariable * freeVariable)
{
    bool res = false;
    if(!this->isRedefined())
    {
    for(size_t i = 0; i < getNumberOfParents(); i++)    // ������� ���� ������������ ������
    {
        ParentLink * plcurr = getParentLink(i);     // ��������� ������������ �����
        if ( get<0>(*plcurr) == formula )     // ���� ������� � ������������ ����� ��������� � ����������� ��������
        {
            if ( freeVariable == nullptr )     // ���� freeVariable ����� nullptr, �� ����������� ������������ ������� ��� ��� �����������
            // �� ��������� ���������� ������������ �����, �� ���� ���������� �������� ������ �� �������
            {
                res = true;    // ��������
                break;
            }
            else    // ���� �������� ��� � �� �������, � �� ����������� ��������� ����������
            {
                EntityVariable * ptstr = get<1>(*plcurr);    // ��������� ���������� �� ��������� ������������ ����� (nullptr ��� ���������� ����������
//				if ( ( ptstr != nullptr ) && ( ptstr->compare(*freeVariable) == 0) )
                if ( ( ptstr != nullptr ) && ( *ptstr == *freeVariable ) )    // ���� ��������� ���������� ���������
                {
                    res = true;    // ��������
                    break;
                }
            }
        }
    }
    }
    return res;
}

//
//	������� ��������� ����� ������� � �������� � EntityBase::text
//
void Formula::putTextOfFormula(vector <EntityBase *> * entities)
{
    text.clear();

    if(this->type == TUPLE)
    {
/*
���������������, ��� ��� ������� ���������� ������ � �����������
        tstring text_add1;
        size_t icount = 0;
        vector <EntityVariable *> * fv = &freeVariables;
        for ( size_t i = 0; i < (fv->size() - 1); i++ )
        {
            if ( icount > 0 )    // ���� ������ ��� ������ �� ����� ����������
                text_add1 += _T(" , ");    // ��������� ������� � ������������ ���������
            text_add1 += *(fv->at(i)->GetText());    // ��������� ����� ������� ����������
            icount++;
        }
        text += _T("<Symbol=/left_tag> ");
        text += text_add1;
        text += _T(" <Symbol=/right_tag>");
        text += _T(" <Symbol=/in> ");
        text += *(fv->at(fv->size() - 1)->GetText()); // ��������� ����� ���������, �������� ����������� ������, ��������� ��� ��������� ��������� ����������
*/
    }
    else if(type == SUBSET)
    {
        SetSubsetText(entities);
    }
//	else if(type == PREDICATE_BELONGING)
//	{
//		SetPredicateText();
//	}
    else
    {

    text = *(getQuantifierPrefix());

//		text += _T("<Symbol=/123>");

    EntityBaseType ft = this->getType();
    if ( ( ft == QUANTIFIER1_OPERATION ) || ( ft == QUANTIFIER2_OPERATION ) )
    {
//		Formula * f = this->getParentLink(0);
        ParentLink * ppl = this->getParentLink(0);
        Formula * f = get<0>(*ppl);
        text += f->getText();
    }
    else
    {
        text += _T(" [ ");

//		proccessOneDetail(formulas, &text, this);
        ParentLink pl(this, nullptr);
        proccessOneDetail(entities, &text, &pl);

//		res_formula += _T("<Symbol=/125>");
        text += _T(" ]");
    }
    }
}

//
//  ������� � ����������� �� �������� ���� ��������� �������� operation ����������, ���� �� ��������� ��� �������� �������� �� ������ ������� �������,
//  ���� ����, �� ���������� ��������� �� ������� ������� � ��������� ���������� possibleVariables (��� ����������� ���������) � possibleFormulas
//  (��� ����������� "�" ��� "���"). ���� �������� �������� ������ ��� (��, ��� ��������, �� ������ ������� ��� ���������) ������������ nullptr
//
Formula * Formula::operationCandidate(vector <EntityBase *> * entities, EntityBaseType operation)
{
    Formula * result = nullptr;
    bool toProccess = true;
    switch ( operation )
    {
    case NEGATIVE_OPERATION:
        if( ( (type != NEGATIVE_OPERATION) || this->isRedefined() ) && ( freeVariables.size() > 0 ) )
        {
            for( size_t i = 0; i < entities->size(); i++)
            {
                EntityBase * base = entities->at(i);
                if ( !base->isFormula() )
                    continue;
                Formula * curr = (Formula *)base;
                if ( curr->inChildOf(this) && curr->isNegative() )
                {
                    toProccess = false;
                    break;
                }
            }
            if(toProccess)
            {
                result = this;
            }
        }
        break;
    case QUANTIFIER1_OPERATION:
    case QUANTIFIER2_OPERATION:
        if ( freeVariables.size() > 0 )
        {
            // ���� � ������� ���� ��������� ����������, �� �������� ��, �� ������� ��� ��� ���� ����� �������
            vector <EntityVariable *> unset;
            if(!this->isRedefined())
// ����� ���� �� ����� ������� �������������� �����������
#ifdef EQUITYTEST

            for( size_t i = 0; i < entities->size(); i++) // ������� �� ���� ��������, ����� ����� ������ �������, ��� ������� ��������.
            {
                EntityBase * base = entities->at(i);
                if ( !base->isFormula() )
                    continue;
                Formula * curr = (Formula *)base;
//				if ( curr->inChildOf(this) && (curr->getType() == operation ) )
                for ( size_t j = 0; j < curr->getNumberOfParents(); j++) // ������� �� ������������ ������ ParentLink ��� ��������� �������
                {
                    ParentLink * ppl = curr->getParentLink(j);
                    // ���� ������������ ������� ��� ��������� ������� � �������� - ����������� ��������
                    if ( ( get<0>(*ppl) == this ) && (curr->getType() == operation ) )
                    {
                        unset.push_back(get<1>(*ppl)); // �� ��������� � unset ����������, �� ������� �������� �������
                    }
                }
            }
#else
            for ( size_t j = 0; j < freeVariables.size(); j++) // ������� �� ��������� ����������
            {
                EntityVariable * pev = freeVariables.at(j);
                Formula * pf = quantifierFormula(operation, pev);
                if( pf != nullptr)
                {
                    for( size_t i = 0; i < entities->size(); i++) // ������� �� ���� ��������, ����� ����� ������ �������, ��� ������� ��������.
                    {
                        EntityBase * pbase = entities->at(i);
                        if ( !pbase->isFormula() )
                            continue;
                        Formula * pformula = (Formula *)pbase;
                        if( *pformula == *pf )    // ���� ������� ������� ��������� ���� � ����� ������������ � �����
                        {
                            unset.push_back(pev); // �� ��������� � unset ����������, �� ������� �������� �������
                            break;
                        }
                    }
                    delete pf;
                }
            }
#endif

            unsetFreeVariables(&unset);
            if( possibleVariables.size() > 0 ) // ���� ����� �������������� ��� ������� �������� ��������� ���������� ������ ����� �� �����
            {
                result = this; // ������ ���������� ��������� ��� ����������� ��������
            }
            unset.clear();
        }
        break;
    case AND_OPERATION:
    case OR_OPERATION:
        possibleFormulas.clear();
        for ( size_t i = 0; i < entities->size(); i++)
        {
            EntityBase * base = entities->at(i);
            if ( !base->isFormula() )
                continue;
            Formula * f = (Formula *)base;
            if( f != this )
            {
                bool found = false;
                if(!this->isRedefined())
                {
                for ( size_t j = 0; j < entities->size(); j++ )
                {
                    EntityBase * base1 = entities->at(j);
                    if ( !base1->isFormula() )
                        continue;
                    Formula * f1 = (Formula *)base1;
                    if ( f1->type == operation )
                    {
                        if ( f1->inChildOf(f) && f1->inChildOf(this) )
                        {
                            found = true;
                            break;
                        }
                    }
                }
                }
                if ( !found )
                    possibleFormulas.push_back(f);
            }
        }
        if ( possibleFormulas.size() > 0 )
            result = this;
        break;
    default:
        break;
    }

    return result;
}


/*
������ ������������, ����� �� ������������.. ��� ����?
void Formula::SetLabel()
{
//	type = FORMULA_SET;
}
*/


tstring makeVarPartOfLabel(vector <EntityBase *> * entities, EntityBase * base)
{
        // ������� ������ ��������� ����������, �������� ������
    tstring res;
    res = _T(" ");
    vector <EntityVariable *> * fv = base->getFreeVariables();
    for (size_t j = 0; j < fv->size(); j++)
    {
        if ( j > 0)
            res += _T(" , ");
        EntityVariable * ev = fv->at(j);
        //������� ����� ����������, ����� ��������, �������� �� �� ������� ����������
        tstring ev_text = *ev->GetText();
        bool found_base = false;
        if(!isTextOfVariable(ev_text)) // ���� �� ��������, ������� �� ������� ��������, �������� �� ���� ����� ������� ��������� ����������
        {
            for (size_t ii = 0; ii < entities->size(); ii++)
            {
                EntityBase * pbase = entities->at(ii);     // ��������� �� ��������� ��������
                if(pbase->isSet())
                {
                    EntityVariable * pnaming = ((FormulaSet *)pbase)->getNaming();
                    if(pnaming != nullptr)
                    {
                        tstring pnaming_text = *(pnaming->GetText()); // ������� ����� ��������������� ��������� ����������
                        if(!pnaming_text.compare(ev_text)) // ���� ����� �������������� ��������� ���������� ��������� � ������ �������
                        {
                            vector <EntityVariable *> freeVars = *(pbase->getFreeVariables()); // ����� �������� ����� ��������� ���������� ����� �������
                            for(size_t iii = 0; iii < fv->size(); iii++)
                            {
                                for(auto p = freeVars.begin(); p != freeVars.end(); ++p)
                                {
                                    if((*p)->compare(*fv->at(iii)))
                                    {
                                        freeVars.erase(p);
                                        break;
                                    }
                                }
                            }
                            for(size_t iii = 0; iii < freeVars.size(); iii++)
                            {
                                if ( iii > 0)
                                    res += _T(" , ");
                                res += *freeVars.at(iii)->GetText();
                            }
                            if(freeVars.size() > 0)
                            {
                                found_base = true;
                                break;
                            }
                        }
                    }
                }
            }

        }
        if(!found_base)
            res += ev_text;
    }
    return res;
}

//
// ������ ����������� �������
//
void Formula::SetLabel(vector <EntityBase *> * entities)
{
    if(this->type == TUPLE)
    {
        int count = 0;
        for( size_t i = 0; i < entities->size(); i++ )
        {
            EntityBase * base = entities->at(i);
            if ( base->isFormula() )
            {
                Formula * f = (Formula *)base;
                if( ( (base->getType() != REPLACE_VARIABLE) && !f->isBelongingPredicate()) ||
                    (base->getType() == REPLACE_VARIABLE))
                {
                    // �������� ��� REPLACE_VARIABLE ���� ����� ���������� �������� ������������� ��������� ���������� � ������ ��������� ���������� ������ 1
                    size_t number_ev = 1;	// ����� ��������� ���������� � ����� �����������
                    EntityVariable * new_var = base->getNewVariable();
                    if(new_var != nullptr)
                    {
                        // ���������, �������� �� ���������� ������������ ��������� ����������
                        tstring symbol = new_var->GetLabel();
                        FormulaSet * pfs = isExistFormulaSet(symbol, new_var->GetIndex(), entities);
                        if(pfs != nullptr)	// ���� ��������� ���������� � ����� ������������ �������
                        {
                            number_ev = pfs->getFreeVariables()->size();
                        }
                    }
                    if(this == base)
                        break;
//					if( !f->isAtom() || ( i == 0 ) || ((base->getType() == REPLACE_VARIABLE) && (number_ev > 1))  )
//						count++;
                    if( ( i == 0 ) || ( !f->isAtom() && ( ( (base->getType() != REPLACE_VARIABLE) && !f->isBelongingPredicate() ) || ( (base->getType() == REPLACE_VARIABLE) && (number_ev > 1) ) ) ) )
                        count++;
                }
            }
        }
        label = _T(" P");
        tstring tstr = to_tstring((long long)count);
        for( size_t i = 0; i < tstr.length(); i++)
        {
            label += _T("<Symbol=/low>");
            label += tstr[i];
        }
        label += _T(" ( ");
        tstring res = makeVarPartOfLabel(entities, this);
        label += res;
        label += _T(" ) ");
    }
    else if(this->type == SUBSET)
    {
        SetSubsetLabel(entities);
    }
    else if(this->type == REPLACE_VARIABLE)
    {
        int count = 0;
        for( size_t i = 0; i < entities->size(); i++ )
        {
            EntityBase * base = entities->at(i);
            if ( base->isFormula() )
            {
                Formula * f = (Formula *)base;
                if( ( (base->getType() != REPLACE_VARIABLE) && !f->isBelongingPredicate()) ||
                    (base->getType() == REPLACE_VARIABLE))
                {
                    size_t number_ev = 1;	// ����� ��������� ���������� � ����� �����������
                    // �������� ��� REPLACE_VARIABLE ���� ����� ���������� �������� ������������� ��������� ���������� � ������ ��������� ���������� ������ 1
                    EntityVariable * new_var = base->getNewVariable();
                    if(new_var != nullptr)
                    {
                        // ���������, �������� �� ���������� ������������ ��������� ����������
                        tstring symbol = new_var->GetLabel();
                        FormulaSet * pfs = isExistFormulaSet(symbol, new_var->GetIndex(), entities);
                        if(pfs != nullptr)	// ���� ��������� ���������� � ����� ������������ �������
                        {
                            number_ev = pfs->getFreeVariables()->size();
                        }
                    }
                    if(this == base)
                        break;
//					if( !f->isAtom() || ( i == 0 ) || (number_ev > 1)  )
//						count++;
                    if( ( i == 0 ) || ( !f->isAtom() && ( ( (base->getType() != REPLACE_VARIABLE) && !f->isBelongingPredicate() ) || ( (base->getType() == REPLACE_VARIABLE) && (number_ev > 1) ) ) ) )
                        count++;
                }
            }
        }
        size_t number_ev = 1;	// ����� ��������� ���������� � ����� �����������
        EntityVariable * new_var = this->getNewVariable();
        if(new_var != nullptr)
        {
            // ���������, �������� �� ���������� ������������ ��������� ����������
            tstring symbol = new_var->GetLabel();
            FormulaSet * pfs = isExistFormulaSet(symbol, new_var->GetIndex(), entities);
            if(pfs != nullptr)	// ���� ��������� ���������� � ����� ������������ �������
            {
                number_ev = pfs->getFreeVariables()->size();
            }
        }
        EntityBase * replaced_base = this->getReplacedBase();
        if((number_ev > 1) || (replaced_base == nullptr))
        {
            label = _T(" P");
            tstring tstr = to_tstring((long long)count);
            for( size_t i = 0; i < tstr.length(); i++)
            {
                label += _T("<Symbol=/low>");
                label += tstr[i];
            }
            if(replaced_base != nullptr)
            {
                // ��������� ����� �� ������ ������ �������� ������� ����� ������ ����������� ����������� �� �����

                EntityVariable * initial_variable = this->getInitialVariable();
                EntityVariable * new_variable = this->getNewVariable();
// ����� ���� ��������� ������ ��� �����������

                tstring text1 = *replaced_base->getLabel();
//				tstring text1 = *replaced_base->getLabel();
                tstring sample = _T("(");
                size_t pos = text1.find(sample);
                if( (pos != tstring::npos) && (text1.length() > (pos + 1)) )
                {
                    text1 = text1.substr(pos + 1);
                    label += _T("( ");
                    tstring res = makeVarPartOfLabel(entities, this);
                    label += res;
                    label += _T(" ) ");
                }
/*
            // ��������� ����� �� ������ ������ �������� ������� ����� ������ ����������� ����������� �� �����
            EntityVariable * initial_variable = this->getInitialVariable();
            EntityVariable * new_variable = this->getNewVariable();
// ����� ���� ��������� ������ ��� �����������
            tstring text1 = *replaced_base->getLabel();
            tstring sample = _T("(");
            size_t pos = text1.find(sample);
            if( (pos != tstring::npos) && (text1.length() > (pos + 1)) )
            {
                text1 = text1.substr(pos + 1);
                label += _T("( ");
                tstring res = makeVarPartOfLabel(entities, this);
                label += res;
                label += _T(" ) ");
            }
*/

//			label += text1;
            }
        }
        else
        {
            label = *replaced_base->getLabel();
//				pnaming->SetLabel(pnaming1->GetLabel());
//				pnaming->SetIndex(pnaming1->GetIndex());
//				tstring redef = pnaming->GetRedefinition();
//				pnaming->SetText();
//				if(redef.length() > 0)
//					pnaming->SetRedefinition(redef);
        }

    }
    else
    {
        int count = 0;
        for( size_t i = 0; i < entities->size(); i++ )
        {
            EntityBase * base = entities->at(i);
//			if ( base->isFormula() && (base->getType() != REPLACE_VARIABLE) )
            if ( base->isFormula() )
            {
                Formula * f = (Formula *)base;
                if( ( (base->getType() != REPLACE_VARIABLE) && !f->isBelongingPredicate()) ||
                    (base->getType() == REPLACE_VARIABLE))
                {
                    // �������� ��� REPLACE_VARIABLE ���� ����� ���������� �������� ������������� ��������� ���������� � ������ ��������� ���������� ������ 1
                    size_t number_ev = 1;	// ����� ��������� ���������� � ����� �����������
                    EntityVariable * new_var = base->getNewVariable();
                    if(new_var != nullptr)
                    {
                        // ���������, �������� �� ���������� ������������ ��������� ����������
                        tstring symbol = new_var->GetLabel();
                        FormulaSet * pfs = isExistFormulaSet(symbol, new_var->GetIndex(), entities);
                        if(pfs != nullptr)	// ���� ��������� ���������� � ����� ������������ �������
                        {
                            number_ev = pfs->getFreeVariables()->size();
                        }
                    }
                    if(this == base)
                        break;
//					if( !f->isAtom() || ( i == 0 ) || (number_ev > 1)  )
//						count++;
                    if( ( i == 0 ) || ( !f->isAtom() && ( ( (base->getType() != REPLACE_VARIABLE) && !f->isBelongingPredicate() ) || ( (base->getType() == REPLACE_VARIABLE) && (number_ev > 1) ) ) ) )
                        count++;
                }
            }
        }
        label = _T(" P");
        tstring tstr = to_tstring((long long)count);
        for( size_t i = 0; i < tstr.length(); i++)
        {
            label += _T("<Symbol=/low>");
            label += tstr[i];
        }
        label += _T(" ( ");
        for ( size_t i = 0; i < freeVariables.size(); i++ )
        {
            if ( i > 0 )
                label += _T(" , ");
            label += *(freeVariables.at(i)->GetText());
        }
        label += _T(" ) ");
    }
}

//
//  ����������� �� ���������
//
FormulaSet::FormulaSet(void)
{
    type = FORMULA_SET;
    set = nullptr;
    pnaming = nullptr;
}

//
// ����������
//
FormulaSet::~FormulaSet(void)
{
/*
    for(size_t i = 0; i < getNumberOfParents(); i++)
    {
        tstring * ptstr = get<1>(*(getParentLink(i)));
        if ( ptstr != nullptr )
            delete ptstr;
        delete getParentLink(i);
    }
*/
    // ����������� ������� ����������
    for ( size_t i = 0; i < baseVariables.size(); i++)
        delete(baseVariables.at(i));
    baseVariables.clear();
    if(pnaming != nullptr)
        delete pnaming;

}

//
// ��������� ���������� �������� ����������, �� ����������� ������, ����� ��� �������� ��� �������� � � ��� � ��� ������� ���� �� ���������� �
// ���� ��������� - �������� ��������������. ������� ���������� true, ���� � ������ ������ ��� ����������
//
bool FormulaSet::isExclusion(Formula * parent)
{
    if( (parent->getNumberOfParents() == 2) &&
        ( (get<0>(*parent->getParentLink(0))->getType() == BELONGING_PREDICATE) || (get<0>(*parent->getParentLink(1))->getType() == BELONGING_PREDICATE) ) )
            return true;
    else
        return false;
}


//
// ��������� ���������� �������� ����������, �� ����������� ������, ����� ��� �������� ��� �������� � � ��� � ��� ������� ���� �� ���������� �
// ���� ��������� - �������� ��������������. ������� ��������� ������� � ��������� ����������, ������� ����������� � ����� �������
//
void FormulaSet::proccessExclusion(Formula * parent, vector <EntityVariable *> * variables, tstring & tvars, tstring & tlevel, bool produceText)
{
//			tstring tvars;
//			tstring tlevel;
            bool first = true;
            for(size_t i = 0; i < parent->getNumberOfParents(); i++) // ������� �� ���� ������������ ������, �� ������� ��������� �������� � (���)
            {
                Formula * pcurr = get<0>(*parent->getParentLink(i));
                vector <EntityVariable *> vev(*pcurr->getFreeVariables());
                vector <EntityVariable *> lost;
                for(size_t i2 = 0; i2 < vev.size(); i2++)
                {
                    bool found = false;
                    for(size_t i1 = 0; i1 < variables->size(); i1++)
                    {
                        if(vev.at(i2)->compare(*variables->at(i1)))
                        {
                            found = true;
                            break;
                        }

                    }
                    if(!found)
                        lost.push_back(vev.at(i2));
                }
                auto vev_end = vev.end();
                for(size_t i1 = 0; i1 < lost.size(); i1++ )
                {
                    vev_end = remove(vev.begin(), vev_end, lost.at(i1));
                }
                if(vev.begin() != vev_end)
                {
                    if(!first)
                    {
                        tvars += _T(",");
                        tlevel += _T(",");
                    }
                    if(pcurr->getType() == BELONGING_PREDICATE)
                    {
                        tvars = _T("<Symbol=/left_tag>");
                        tlevel = _T("<");
                    }
                    for(auto pit = vev.begin(); pit != vev_end; ++pit)
                    {
                        if(pit != vev.begin())
                        {
                            tvars += _T(",");
                            tlevel += _T(",");
                        }
                        tvars += *((*pit)->GetText());
                        EntityVariable * pev1 = *pit;
                        tlevel += ((Level *)pev1)->GetLevel();
                    }
                    if(pcurr->getType() == BELONGING_PREDICATE)
                    {
                        tvars += _T("<Symbol=/right_tag>");
                        tlevel += _T(">");
                    }
                    first = false;
                }
            }
            tlevel = _T("<") + tlevel + _T(">");
            tvars = _T("<Symbol=/left_tag>") + tvars + _T("<Symbol=/right_tag>");
            if(pnaming != nullptr)
                ((Level *)pnaming)->SetLevel(tlevel);
            if(produceText)
                setText(tvars);
}


//
// ����������� ��� ���������� ��������� ���������� �� ��������� �� ������������ ������� � ��������� ������������ ��������� ����������
//
FormulaSet::FormulaSet(Formula * parent, vector <EntityVariable *> * variables, EntityVariable * pnaming_)
{
    type = FORMULA_SET;
    set = nullptr;
    pnaming = nullptr;
    if(pnaming_ != nullptr)
        pnaming = new EntityVariable(*pnaming_);
//		pnaming = new NamingVariable(*pnaming_);
    formula = parent;
    bool already_proccessed = false;
    tstring tevs;
    // ��������� ���������� �������� ����������, �� ����������� ������, ����� ��� �������� ��� �������� � � ��� � ��� ������� ���� �� ���������� �
    // ���� ��������� - �������� ��������������. ���� if-���� ������������� ��� ����������
    if( (parent->getType() == AND_OPERATION) || (parent->getType() == AND_OPERATION) )
    {
        if( (parent->getNumberOfParents() == 2) &&
            ( (get<0>(*parent->getParentLink(0))->getType() == BELONGING_PREDICATE) || (get<0>(*parent->getParentLink(1))->getType() == BELONGING_PREDICATE) ) )
        {
            tstring tvars;
            tstring tlevel;
            bool first = true;
            for(size_t i = 0; i < parent->getNumberOfParents(); i++) // ������� �� ���� ������������ ������, �� ������� ��������� �������� � (���)
            {
                Formula * pcurr = get<0>(*parent->getParentLink(i));
                vector <EntityVariable *> vev(*pcurr->getFreeVariables());
                vector <EntityVariable *> lost;
                for(size_t i2 = 0; i2 < vev.size(); i2++)
                {
                    bool found = false;
                    for(size_t i1 = 0; i1 < variables->size(); i1++)
                    {
                        if(vev.at(i2)->compare(*variables->at(i1)))
                        {
                            found = true;
                            break;
                        }

                    }
                    if(!found)
                        lost.push_back(vev.at(i2));
                }
                auto vev_end = vev.end();
                for(size_t i1 = 0; i1 < lost.size(); i1++ )
                {
                    vev_end = remove(vev.begin(), vev_end, lost.at(i1));
                }
                if(vev.begin() != vev_end)
                {
                    if(!first)
                    {
                        tvars += _T(",");
                        tlevel += _T(",");
                    }
                    if(pcurr->getType() == BELONGING_PREDICATE)
                    {
                        tvars = _T("<Symbol=/left_tag>");
                        tlevel = _T("<");
                    }
                    for(auto pit = vev.begin(); pit != vev_end; ++pit)
                    {
                        if(pit != vev.begin())
                        {
                            tvars += _T(",");
                            tlevel += _T(",");
                        }
                        tvars += *((*pit)->GetText());
                        EntityVariable * pev1 = *pit;
                        tlevel += ((Level *)pev1)->GetLevel();
                    }
                    if(pcurr->getType() == BELONGING_PREDICATE)
                    {
                        tvars += _T("<Symbol=/right_tag>");
                        tlevel += _T(">");
                    }
                    first = false;
                }
            }
            tlevel = _T("<") + tlevel + _T(">");
            tvars = _T("<Symbol=/left_tag>") + tvars + _T("<Symbol=/right_tag>");
            if(pnaming != nullptr)
                ((Level *)pnaming)->SetLevel(tlevel);
            setText(tvars);
            already_proccessed = true;
        }
    }
    vector <EntityVariable *> *fv = parent->getFreeVariables();
    for ( size_t i = 0; i < fv->size(); i++)
    {
        EntityVariable * pev = new EntityVariable(*(fv->at(i)));
        // ������������ � ����������� ��������� ���������� variables ����������� �� ����� ��������� ����������
        bool found_fv = false;
        for ( size_t i1 = 0; i1 < variables->size(); i1++)
        {
            if(pev->compare(*variables->at(i1)))
            {
                found_fv = true;
                break;
            }
        }
        if(!found_fv)
            freeVariables.push_back(pev);
    }
    for ( size_t i = 0; i < variables->size(); i++)
    {
        EntityVariable * pev = new EntityVariable(*(variables->at(i)));
        baseVariables.push_back(pev);
//			ParentLink * pl = new ParentLink(parent, ptstr);
    }
    if(!already_proccessed)
    {
        setText();
    }
}

/*
���������� ������, ��� �����������
FormulaSet::FormulaSet(Formula * parent, vector <EntityVariable *> * variables)
{
    type = FORMULA_SET;
    set = nullptr;
    vector <EntityVariable *> *fv = parent->getFreeVariables();
    for ( size_t i = 0; i < fv->size(); i++)
    {
        EntityVariable * pev = new EntityVariable(*(fv->at(i)));
        freeVariables.push_back(pev);
    }
    for ( size_t i = 0; i < variables->size(); i++)
    {
        EntityVariable * pev = new EntityVariable(*(variables->at(i)));
        baseVariables.push_back(pev);
//		ParentLink * pl = new ParentLink(parent, ptstr);
    }
    formula = parent;
    setText();
}
*/


//
//  ����� ��������� ����� ��������� ����������
//
void FormulaSet::setText()
{
    if(type == FORMULA_SET) //���� �� ������������, � ��������� ����������
    {
        text = _T(" { ");  // ����� �������� ������
//		for ( size_t i = 0; i < getNumberOfParents() ; i++ )
        size_t size = baseVariables.size();
        if ( size > 1) // ���� ���������� ���� �� ���� ������� ����������, ���������� �������
            text += _T("<Symbol=/left_tag> "); // ����������� ������ ����
        // ���� �� ������� ����������
        for ( size_t i = 0; i < size ; i++ )
        {
            if (i > 0) // ���� ��� ������ ������� ����������
                text += _T(" , "); // �������� ������� ����� �����������, ���������� ���������
            text += *baseVariables.at(i)->GetText(); // ��������� ���������� ����� ��������� ������� ����������
        }
        if ( size > 1) // ���� ���������� ���� �� ���� ������� ����������, ���������� �������
            text += _T("<Symbol=/right_tag> "); // ����������� ������� ����
/*
//		������ ������� ���������� ������ ��������� ����������
        tstring label = *formula->getRedefinedText();
        trimWhitespaces(&label);
        if(label.length() == 0)
        {
            label = *formula->getLabel();
            trimWhitespaces(&label);
        }
*/
        tstring label = formula->getText();
        trimWhitespaces(&label);
        if( (label.length() > 0) && (label[0] == TCHAR('[')) )
        {
            label = label.substr(1);
        }
        if( (label.length() > 0) && (label[label.length() - 1] == TCHAR(']')) )
        {
            label = label.substr(0, label.length() - 1);
        }
        trimWhitespaces(&label);
        text += _T(" | ") + label; // ��������� ����������� � ��������� �� ��� ����������� �������-��������
        text += _T(" }"); // ��������� ������ �������� ������
    }
}


//
//  ����� ��������� ����� ��������� ���������� ��� ������� ������������� ������ ��� ����������
//
void FormulaSet::setText(tstring tvars)
{
    if(type == FORMULA_SET) //���� �� ������������, � ��������� ����������
    {
        text = _T(" { ");  // ����� �������� ������
        text += tvars;
/*
//		������ ������� ���������� ������ ��������� ����������
        tstring label = *formula->getRedefinedText();
        trimWhitespaces(&label);
        if(label.length() == 0)
        {
            label = *formula->getLabel();
            trimWhitespaces(&label);
        }
*/
        tstring label = formula->getText();
        trimWhitespaces(&label);
        if( (label.length() > 0) && (label[0] == TCHAR('[')) )
        {
            label = label.substr(1);
        }
        if( (label.length() > 0) && (label[label.length() - 1] == TCHAR(']')) )
        {
            label = label.substr(0, label.length() - 1);
        }
        trimWhitespaces(&label);
        text += _T(" | ") + label; // ��������� ����������� � ��������� �� ��� ����������� �������-��������
        text += _T(" }"); // ��������� ������ �������� ������
    }
}


//
//  ����� �������� � ������ ������������ ��������  ��������� ���������� �� ������������
//
void Formula::SetSubsetText(tstring & set_text)
{
    tstring f = _T(" <Symbol=/fuzzy> ");
    size_t pos = text.find(f);
    if(pos != tstring::npos)
    {
        tstring new_text = text.substr(0, pos + f.length());
        new_text += _T("( ") + set_text + _T(" )");
        text = new_text;
    }
}

//
//  ����� ��������� ����� ������������ ����������
//
void Formula::SetSubsetText(vector <EntityBase *> * entities)
{
    if(type == SUBSET) //���� ������������, ��������, ���������� ��������
    {
        tstring add;
        size_t size_fv = freeVariables.size();
        if(size_fv > 1)
        {
            text = *freeVariables.at(size_fv - 1)->GetText();
            text += _T("(");
//			EntityBase * set_base = (EntityBase *)parent_set;
//			vector <EntityVariable *> * fv_of_set = parent_set->getFreeVariables();
            vector <EntityVariable *> * fv_of_set = getFreeVariables();
            int count_v = 0;
            for(size_t i = 0; i < (freeVariables.size() - 1); i++)
            {
                if (count_v > 0) // ���� ��� ������ ������� ����������
                    add += _T(" , "); // �������� ������� ����� �����������, ���������� ���������
                add += *freeVariables.at(i)->GetText(); // ��������� ���������� ����� ��������� ������� ����������
                count_v++;
            }
            text += add;
            text += _T(")");
            text += _T(" <Symbol=/fuzzy> "); // ����������� ������� ����
            text += *parent_set->getLabel();
/*
            // ������ ����� ������ ����������� �� ����������� ������������� ��������� ����������, ������� �� ������� setLabal
            int count = 0;
            bool isMixed = false;
            for (size_t i = 0; i < entities->size(); i++)
            {
                EntityBase * base = entities->at(i);
                if(base == parent_set)
                    break;
                if( base->getType() == FORMULA_SET )
                {
                    FormulaSet * pfsbase = (FormulaSet *)base;
                    if( parent_set->isSetBased() && pfsbase->isSetBased() )
                        count++;
                    if( parent_set->isVariableBased() && pfsbase->isVariableBased() )
                        count++;

                }
            }
            if(parent_set->isSetBased())
                text += _T("R");
            else if(parent_set->isVariableBased())
                text += _T("M");
            else
                isMixed = true;
            if(!isMixed)
            {
                tstring tstr = to_tstring((long long)count);
                for( size_t i = 0; i < tstr.length(); i++)
                {
                    text += _T("<Symbol=/low>");
                    text += tstr[i];
                }
                text += _T(" ( ");
                text += add;
                text += _T(" ) ");
            }
            else
            {
                text += *parent_set->getRedefinedText();
            }
*/
        }
        else
        {
            text = *freeVariables.at(size_fv - 1)->GetText();
            text += _T("()");
            text += _T(" <Symbol=/fuzzy> "); // ����������� ������� ����
            text += *parent_set->getLabel();
        }
    }
}

//
//  ����� ������ ��������� ���������� ��� ������� ������� � ���������� ��������� �� ����, � ������ ������������� ��������� ����� ���������
//  ���������� nullptr
//
//FormulaSet * Formula::makeFormulaSet(vector <EntityBase *> * entities, vector <EntityVariable *> * variables)
FormulaSet * Formula::makeFormulaSet(vector <EntityBase *> * entities, vector <EntityVariable *> * variables, EntityVariable * pnaming)
{
    FormulaSet * set = nullptr;
    bool found = false;
    for ( size_t i = 0; i < entities->size(); i++ )
    {
        EntityBase * base = entities->at(i);
        if ( !base->isSet() )
            continue;
        FormulaSet * set = (FormulaSet *)base;
        if ( set->getParentFormula() == this )
        {
            found = true;
            break;
        }
    }
    if ( !found )
    {
        set = new FormulaSet(this, variables, pnaming);
    }
    return set;
}


//
//  ����� ����������, �������� �� ��� ������� ������� ��������� ��������� ����������. � ������ �������� ���������� ��������� �� ������� �������,
// ���� ���������� (��� ���������) - ���������� nullptr
//
Formula * Formula::formulasetCandidate(vector <EntityBase *> * entities)
{
    Formula * set = nullptr;
    bool found = false;
    for ( size_t i = 0; i < entities->size(); i++ )
    {
        EntityBase * base = entities->at(i);
        if ( !base->isSet() )
            continue;
        FormulaSet * set = (FormulaSet *)base;
        if ( set->getParentFormula() == this )
        {
            found = true;
            break;
        }
    }
    if ( !found )
        set = this;
    return set;
}


//
//  ���������� ��� ��������� ���������� ��������� ��� ������ ������ ��������� ���������� - ����������
//
bool FormulaSet::isVariableBased()
{
    bool res = true;
    for(size_t i = 0; i < baseVariables.size(); i++)
    {
        EntityVariable * tev = baseVariables.at(i);
        if(!tev->isVariable() )
        {
            res = false;
            break;
        }
    }
    return res;
}

//
// ���������� ��� ��������� ���������� ��������� ��� ������ ��������� ���������� - ��������
//
bool FormulaSet::isSetBased()
{
    bool res = true;
    for(size_t i = 0; i < baseVariables.size(); i++)
    {
        EntityVariable * tev = baseVariables.at(i);
        if(!tev->isSet() )
        {
            res = false;
            break;
        }
    }
    return res;
}



//
//  ����� ������ ����������� ��� ��������� ����������
//
void FormulaSet::SetLabel(vector <EntityBase *> * entities)
{
    int count = 0;
    bool isMixed = false;
    EntityBase * peb_replaced = this->getReplacedBase();
/*
    if( (type == REPLACE_VARIABLE) && (peb_replaced != nullptr) && ( ((FormulaSet *)peb_replaced)->getNaming() != nullptr) )
    {
        EntityVariable * pnaming1 = ((FormulaSet *) peb_replaced)->getNaming();	// ������������ �������� ��������� ����������
        size_t number_ev = peb_replaced->getFreeVariables()->size();	// ����� ��������� ���������� � ������� ��������� ����������
if((new_variable != nullptr) && (!new_variable->GetRedifinition().length())
        if(number_ev > 1)	// ���� ������ 1, �� ������ ����������� � ��� �� �������� � ������ �������� � ����� ������������� ��������
        {
            tstring symbol = pnaming1->GetLabel();
            int i = 0;
            tstring index = to_tstring((long long)i);
            while(isExistVariable(symbol, index, entities) || isExistNaming(symbol, index, entities))	// ���� ����� ���������� �� ������� � �����
            {
                i++;
                index = to_tstring((long long)i);
            }
            if(pnaming != nullptr)
            {
                pnaming->SetLabel(symbol);
                pnaming->SetIndex(index);
                tstring redef = pnaming->GetRedefinition();
                pnaming->SetText();
                if(redef.length() > 0)
                    pnaming->SetRedefinition(redef);
                label = *pnaming->GetInitialText();
            }
            else
            {
                pnaming = new EntityVariable(symbol, index, SET);
                pnaming->SetLevel(pnaming1->GetLevel());
            }
        }
        else
        {
            if(pnaming != nullptr)
            {
                pnaming->SetLabel(pnaming1->GetLabel());
                pnaming->SetIndex(pnaming1->GetIndex());
                tstring redef = pnaming->GetRedefinition();
                pnaming->SetText();
                if(redef.length() > 0)
                    pnaming->SetRedefinition(redef);
            }
            else
            {
                pnaming = new EntityVariable(*pnaming1);
                pnaming->SetLevel(pnaming1->GetLevel());
            }
            label = *pnaming->GetInitialText();
        }
    }
    else if(pnaming != nullptr)
    {
        label = *pnaming->GetText();
    }
*/
    if( (type == REPLACE_VARIABLE) && (peb_replaced != nullptr) && ( ((FormulaSet *)peb_replaced)->getNaming() != nullptr) )
    {
        EntityVariable * pnaming1 = ((FormulaSet *) peb_replaced)->getNaming();	// ������������ �������� ��������� ����������

//		size_t number_ev = peb_replaced->getFreeVariables()->size();	// ����� ��������� ���������� � ������� ��������� ����������
        size_t number_ev = 1;	// ����� ��������� ���������� � ����� �����������
        if(new_variable != nullptr)
        {
            // ���������, �������� �� ���������� ������������ ��������� ����������
            tstring symbol = new_variable->GetLabel();
            FormulaSet * pfs = isExistFormulaSet(symbol, new_variable->GetIndex(), entities);
            if(pfs != nullptr)	// ���� ��������� ���������� � ����� ������������ �������
            {
                number_ev = pfs->getFreeVariables()->size();
            }
        }
        if(number_ev > 1)	// ���� ������ 1, �� ������ ����������� � ��� �� �������� � ������ �������� � ����� ������������� ��������
        {
            tstring symbol = pnaming1->GetLabel();
            int i = 0;
            tstring index = to_tstring((long long)i);
            while(isExistVariable(symbol, index, entities) || isExistNaming(symbol, index, entities))	// ���� ����� ���������� �� ������� � �����
            {
                i++;
                index = to_tstring((long long)i);
            }
            if(pnaming != nullptr)
            {
                pnaming->SetLabel(symbol);
                pnaming->SetIndex(index);
                tstring redef = pnaming->GetRedefinition();
                pnaming->SetText();
                if(redef.length() > 0)
                    pnaming->SetRedefinition(redef);
                label = *pnaming->GetInitialText();
            }
            else
            {
                pnaming = new EntityVariable(symbol, index, SET);
                pnaming->SetLevel(pnaming1->GetLevel());
            }
        }
        else
        {
            if(pnaming != nullptr)
            {
                pnaming->SetLabel(pnaming1->GetLabel());
                pnaming->SetIndex(pnaming1->GetIndex());
                tstring redef = pnaming->GetRedefinition();
                pnaming->SetText();
                if(redef.length() > 0)
                    pnaming->SetRedefinition(redef);
            }
            else
            {
                pnaming = new EntityVariable(*pnaming1);
                pnaming->SetLevel(pnaming1->GetLevel());
            }
            label = *pnaming->GetInitialText();
        }
    }
    else if(pnaming != nullptr)
    {
        label = *pnaming->GetText();
    }
    else
    {
        for (size_t i = 0; i < entities->size(); i++)
        {
            EntityBase * base = entities->at(i);
            if( base->getType() == FORMULA_SET )
            {
                FormulaSet * pfsbase = (FormulaSet *)base;
                if( this->isSetBased() && pfsbase->isSetBased() )
                    count++;
                if( this->isVariableBased() && pfsbase->isVariableBased() )
                    count++;

            }
        }
        if(isSetBased())
            label = _T("R");
        else if(isVariableBased())
            label = _T("M");
        else
            isMixed = true;
        if(!isMixed)
        {
            tstring tstr = to_tstring((long long)count);
            for( size_t i = 0; i < tstr.length(); i++)
            {
                label += _T("<Symbol=/low>");
                label += tstr[i];
            }
        }
        else
            label = text;
    }
    label += _T(" ( ");
    tstring res = makeVarPartOfLabel(entities, this);
    label += res;

/*
    int count1 = 0;
    for ( size_t i = 0; i < freeVariables.size(); i++ )
    {
        EntityVariable * pfv = freeVariables.at(i);
        bool isFound = false;
        for( size_t i1 = 0; i1 < baseVariables.size(); i1++)
        {
            if( *pfv == *(baseVariables.at(i1) ) )
            {
                isFound = true;
                break;
            }
        }
        if( !isFound )
        {
            if ( count1 > 0 )
                label += _T(" , ");
            count1++;
                label += *(pfv->GetText());
        }
*/
/*
        if( isSetBased() == pfv->isSet() )
        {
            if ( count1 > 0 )
            {
                label += _T(" , ");
                count1++;
            }
            label += *(pfv->GetText());
        }
    }
*/
    label += _T(" ) ");
}




/*
//
//	���������� ����������� ��� ���������� Formula
//
Formula::Formula(const Formula& fi)
{
    label = fi.Label;
    description = fi.Description;
    addons = fi.Addons;
    text = fi.Text;
    feature = fi.Feature;
    type = fi.EntityType;
    for ( int i = 0; i < fi.freeVariables.size(); i++)
    {
        EntityVariable * pv = new EntityVariable(*(fi.FreeVariables[i]));
        freeVariables.push_back(pv);
    }
}


//
//	���������� ����������� ��� ���������� FormulaSet
//
FormulaSet::FormulaSet(const FormulaSet& si)
{
    label = si.Label;
    description = si.Description;
    addons = si.Addons;
    text = si.Text;
    type = si.EntityType;
    for ( int i = 0; i < si.FreeVariables.GetSize(); i++)
    {
        EntityVariable * pv = new EntityVariable(*(si.FreeVariables[i]));
        freeVariables.push_back(pv);
    }
    for ( int i = 0; i < si.BaseVariables.GetSize(); i++)
    {
        EntityVariable * pv = new EntityVariable(*(si.BaseVariables[i]));
        baseVariables.push_back(pv);
    }
}
*/

void EntityBase::SetText(const tstring lpctstr)
{
    tstring tstr = lpctstr;
    trimWhitespaces(&tstr);
//	removeDoubledWhitespaces(&tstr);
    removeAllWhitespaces(&tstr);
    tstring text1;
        text1 = text;
    trimWhitespaces(&text1);
//	removeDoubledWhitespaces(&text1);
    removeAllWhitespaces(&text1);
    if(text1.compare(tstr))
        redefined_text = lpctstr;
};

int Formula::getNumberOfParents(bool ignoreRedefined)
{
    if(!ignoreRedefined && isRedefined())
        return 0;
    else
        return parents.size();
}

// �������� ��������� �������������, ��� ��������, ��������������, ��� ��� ������� ���������� ����� ��� �������� ��������� ����������
bool Formula::predicateBelonging(vector <EntityBase *> * entities, Formula * parent, FormulaSet * set, tstring * ptvars)
{
//	feature = PERFORMED_FEATURE;    // "���������"
    type = BELONGING_PREDICATE;    // ��������� ��� - �������� ��������������
    // ��������� ��������� ���������� �� �������, �� ������� �������� ��������� ���������� � �������� ��������������
    vector <EntityVariable *> *fv = parent->getFreeVariables();
    vector <EntityVariable *> *bv = set->getBaseVariables();
    for ( size_t i = 0; i < fv->size(); i++)
    {
        EntityVariable * pev = new EntityVariable(*(fv->at(i)));
        freeVariables.push_back(pev);
    }
    parent_set = set;
/*
    // �������� ��������� ���������� �� ����������� ��������� ����������
    // ������ ����� ������ ����������� �� ����������� ������������� ��������� ����������, ������� �� ������� setLabal
    if(set->isVariableBased() || set->isSetBased())
    {
        int count = 0;
        bool isMixed = false;
        for (size_t i = 0; i < entities->size(); i++)
        {
            EntityBase * base = entities->at(i);
            if(base == parent_set)
                break;
            if( base->getType() == FORMULA_SET )
            {
                FormulaSet * pfsbase = (FormulaSet *)base;
                if( parent_set->isSetBased() && pfsbase->isSetBased() )
                    count++;
                if( parent_set->isVariableBased() && pfsbase->isVariableBased() )
                    count++;
            }
        }
        tstring variable_symbol;
        tstring variable_index = to_tstring((long long)count);
        if(parent_set->isSetBased())
            variable_symbol = _T("R");
        else if(parent_set->isVariableBased())
            variable_symbol = _T("M");
        EntityVariable * pev_set = new EntityVariable(variable_symbol, variable_index, SET);
        freeVariables.push_back(pev_set);
    }
*/
    // ������ ����������� ��� ��������� ��������������
    int count = 0;
    if( parent->type != ATOMIC_FORMULA)
    {
        for( size_t i = 0; i < entities->size(); i++ )
        {
            EntityBase * base = entities->at(i);
            if ( base->isFormula() )
            {
                Formula * f = (Formula *)base;
                // �������� ��� REPLACE_VARIABLE ���� ����� ���������� �������� ������������� ��������� ���������� � ������ ��������� ���������� ������ 1
                size_t number_ev = 1;	// ����� ��������� ���������� � ����� �����������
                EntityVariable * new_var = base->getNewVariable();
                if(new_var != nullptr)
                {
                    // ���������, �������� �� ���������� ������������ ��������� ����������
                    tstring symbol = new_var->GetLabel();
                    FormulaSet * pfs = isExistFormulaSet(symbol, new_var->GetIndex(), entities);
                    if(pfs != nullptr)	// ���� ��������� ���������� � ����� ������������ �������
                    {
                        number_ev = pfs->getFreeVariables()->size();
                    }
                }
//				if( (!f->isAtom() && !f->isBelongingPredicate() ) || (number_ev > 1) )
//					count++;
                if( (( i == 0 ) && !f->isAtom()) || ( !f->isAtom() && ( ( (base->getType() != REPLACE_VARIABLE) && !f->isBelongingPredicate() ) || ( (base->getType() == REPLACE_VARIABLE) && (number_ev > 1) ) ) ) )
                    count++;
                if(parent == base)
                    break;
            }
        }
    }
    label = _T(" P");
    label += _T("<Symbol=/low>");
    label += _T("0");
    tstring tstr = to_tstring((long long)count);
    for( size_t i = 0; i < tstr.length(); i++)
    {
        label += _T("<Symbol=/low>");
        label += tstr[i];
    }
    label += _T(" ( ");
    for ( size_t i = 0; i < fv->size(); i++ )
    {
        if ( i > 0 )
            label += _T(" , ");
        label += *(fv->at(i)->GetText());
    }
    label += _T(" ) ");

    // ������ ����� �������
    SetPredicateText(parent, ptvars);
    return true;
}

// ������������� ����� ��������� ��������������, ���������� ����� ��� ��������� ����������, �� �������� �������� �������� ��������������
void Formula::SetPredicateText(tstring & set_text)
{
    tstring f = _T(" <Symbol=/in> ");
    size_t pos = text.find(f);
    if(pos != tstring::npos)
    {
        tstring new_text = text.substr(0, pos + f.length());
        new_text += _T("{ ") + set_text + _T(" }");
        text = new_text;
    }
}

// ������ ����� ��������� ��������������
void Formula::SetPredicateText(Formula * parent, tstring * ptvars)
{
    vector <EntityVariable *> *fv = parent->getFreeVariables();
    vector <EntityVariable *> *bv = parent_set->getBaseVariables();
    text.clear();
    if(ptvars != nullptr)
    {
        text = *ptvars;
    }
    else
    {
        tstring text_add1;
        size_t icount = 0;
        for ( size_t i = 0; i < fv->size(); i++ )
        {
            EntityVariable * pev = new EntityVariable(*(fv->at(i)));
            bool found = false;
            for( size_t ii = 0; ii < bv->size(); ii++)
            {
                if(pev->compare(*(bv->at(ii))))
                {
                    found = true;
                    break;
                }
            }
            if(found)
            {
                if ( icount > 0 )    // ���� ������ ��� ������ �� ����� ����������
                    text_add1 += _T(" , ");    // ��������� ������� � ������������ ���������
                text_add1 += *(fv->at(i)->GetText());    // ��������� ����� ������� ����������
                icount++;
            }
        }
        if(icount > 1)
            text += _T("<Symbol=/left_tag> ");
        text += text_add1;
        if(icount > 1)
            text += _T(" <Symbol=/right_tag>");
    }
    text += _T(" <Symbol=/in> ");
//	if(parent_set->isRedefined())
//	{
//		tstring redefined = ((EntityBase *)parent_set)->getText();
//		trimWhitespaces(&redefined);
//		text += redefined;
//	}
//	else
//		text += *parent_set->getLabel();
    EntityVariable * pnaming = parent_set->getNaming();
    if( (pnaming != nullptr) && (pnaming->GetRedefinition().length() > 0))
    {
        text += _T("( ") + *(pnaming->GetText()) + _T(") ");
    }
    else
        text += *parent_set->getLabel();

}

//
// �������� ������������, entities - ������ ���������� �� ������� � ��������� �����, set - ���������� ��� ������������ ���������, variables - ������ ���������� ��
// ��������� ����������, ������� ����� ������� � ��������� ���������� ������.���� ��������, ����� �������� ������ ��������� ���������� ��� ������������
//
bool Formula::subset(vector <EntityBase *> * entities, FormulaSet * set, vector <EntityVariable *> * variables)
{
    bool result = true;
    if(!entities || !set || !variables)
        result = false;
    type = SUBSET;
    feature = PERFORMED_FEATURE;    // "���������"
//	type = FORMULA_SET;
//	vector <EntityVariable *> *fv = parent->getFreeVariables();
//	for ( size_t i = 0; i < fv->size(); i++)
//	{
//		EntityVariable * pev = new EntityVariable(*(fv->at(i)));
//		freeVariables.push_back(pev);
//	}
    parent_set = set;
/*
    for ( size_t i = 0; i < variables->size(); i++)
    {
        EntityVariable * pev = new EntityVariable(*(variables->at(i)));
        freeVariables.push_back(pev);
//		ParentLink * pl = new ParentLink(parent, ptstr);
    }
*/
    vector <EntityVariable *> * fv_of_set = parent_set->getFreeVariables();
    for(size_t i = 0; i < fv_of_set->size(); i++)
    {
        bool found_v = false;
        for(size_t i1 = 0; i1 < variables->size(); i1++)
        {
            if(fv_of_set->at(i)->compare(*variables->at(i1)))
            {
                found_v = true;
                break;
            }
        }
        if(!found_v)
        {
            EntityVariable * pev = new EntityVariable(*(fv_of_set->at(i)));
            freeVariables.push_back(pev);
        }
    }
    EntityVariable * psubset = new EntityVariable(*variables->at(variables->size()- 1));
    freeVariables.push_back(psubset);
/*
    for(size_t i = 0; i < fv_of_set->size(); i++)
    {
                bool found_v = false;
                for(size_t i1 = 0; i1 < size_fv; i1++)
                {
                    if(fv_of_set->at(i)->compare(*freeVariables.at(i1)))
                    {
                        found_v = true;
                        break;
                    }
                }
                if(!found_v)
                {
                    if (count_v > 0) // ���� ��� ������ ������� ����������
                        text += _T(" , "); // �������� ������� ����� �����������, ���������� ���������
                    add += *fv_of_set->at(i)->GetText(); // ��������� ���������� ����� ��������� ������� ����������
                    count_v++;
                }
            }
*/
    return result;
}


//
//  ����� ������ ����������� ��� ������������
//
void Formula::SetSubsetLabel(vector <EntityBase *> * entities)
{
    size_t number_ev = 1;	// ����� ��������� ���������� � ����� �����������
    if(type == SUBSET) //���� ������������, ��������, ���������� ��������
    {
        tstring add;
        size_t size_fv = freeVariables.size();
/*
        if(size_fv > 1)
        {
            label = *freeVariables.at(size_fv - 1)->GetText();
            vector <EntityVariable *> * fv_of_set = parent_set->getFreeVariables();
            int count_v = 0;
            for(size_t i = 0; i < fv_of_set->size(); i++)
            {
                bool found_v = false;
                for(size_t i1 = 0; i1 < size_fv; i1++)
                {
                    if(fv_of_set->at(i)->compare(*freeVariables.at(i1)))
                    {
                        found_v = true;
                        break;
                    }
                }
                if(!found_v)
                {
                    if (count_v > 0) // ���� ��� ������ ������� ����������
                        add += _T(" , "); // �������� ������� ����� �����������, ���������� ���������
                    add += *fv_of_set->at(i)->GetText(); // ��������� ���������� ����� ��������� ������� ����������
                    count_v++;
                }
            }
            int count = 0;
            for( size_t i = 0; i < entities->size(); i++ )
            {
                EntityBase * base = entities->at(i);
                if ( base->isFormula() )
                {
                    if(this == base)
                        break;
                    Formula * f = (Formula *)base;
                    if( ( !f->isAtom() || ( i == 0 ) ) && !f->isBelongingPredicate())
                        count++;
                }
            }
            label = _T(" P");
            tstring tstr = to_tstring((long long)count);
            for( size_t i = 0; i < tstr.length(); i++)
            {
                label += _T("<Symbol=/low>");
                label += tstr[i];
            }
            label += _T("(");
//			EntityBase * set_base = (EntityBase *)parent_set;
            label += *freeVariables.at(size_fv - 1)->GetText();
            label += _T(",");
            label += *parent_set->getLabel();
            label += _T(")");
        }
*/
        tstring res = makeVarPartOfLabel(entities, this);
        add += res;
/*
        int count_v = 0;
        for(size_t i = 0; i < freeVariables.size(); i++)
        {
            if (count_v > 0) // ���� ��� ������ ������� ����������
                add += _T(" , "); // �������� ������� ����� �����������, ���������� ���������
            add += *freeVariables.at(i)->GetText(); // ��������� ���������� ����� ��������� ������� ����������
            count_v++;
        }
*/
        int count = 0;
        for( size_t i = 0; i < entities->size(); i++ )
        {
            EntityBase * base = entities->at(i);
            if ( base->isFormula() )
            {
                Formula * f = (Formula *)base;
                if( ( (base->getType() != REPLACE_VARIABLE) && !f->isBelongingPredicate()) ||
                    (base->getType() == REPLACE_VARIABLE))
                {
                    // �������� ��� REPLACE_VARIABLE ���� ����� ���������� �������� ������������� ��������� ���������� � ������ ��������� ���������� ������ 1
                    EntityVariable * new_var = base->getNewVariable();
                    if(new_var != nullptr)
                    {
                        // ���������, �������� �� ���������� ������������ ��������� ����������
                        tstring symbol = new_var->GetLabel();
                        FormulaSet * pfs = isExistFormulaSet(symbol, new_var->GetIndex(), entities);
                        if(pfs != nullptr)	// ���� ��������� ���������� � ����� ������������ �������
                        {
                            number_ev = pfs->getFreeVariables()->size();
                        }
                    }
                    if(this == base)
                        break;
//					if( !f->isAtom() || ( i == 0 ) || (number_ev > 1)  )
//						count++;
                    if( ( i == 0 ) || ( !f->isAtom() && ( ( (base->getType() != REPLACE_VARIABLE) && !f->isBelongingPredicate() ) || ( (base->getType() == REPLACE_VARIABLE) && (number_ev > 1) ) ) ) )
                        count++;
                }
            }
        }
        EntityBase * replaced_base = this->getReplacedBase();
        if((number_ev > 1) || (replaced_base == nullptr))
        {
            label = _T(" P");
            tstring tstr = to_tstring((long long)count);
            for( size_t i = 0; i < tstr.length(); i++)
            {
                label += _T("<Symbol=/low>");
                label += tstr[i];
            }
            label += _T("(");
            if(add.length() > 0)
            {
                label += _T(" ") + add + _T(" ");
            }
            label += _T(")");
        }
        else
        {
            label = *replaced_base->getLabel();
        }
    }
}


Tuple::Tuple(void)
{
//	dobavka=TCHAR(' ');
    type = TUPLE;
    level = 0;
    feature = PERFORMED_FEATURE;    // "���������"
}

Tuple::Tuple(EntityVariable & ev1, EntityVariable & set)
{
//	dobavka=TCHAR(' ');
    type = TUPLE;
    level = 0;
    feature = PERFORMED_FEATURE;    // "���������"
    freeVariables.push_back(new EntityVariable(ev1));
    freeVariables.push_back(new EntityVariable(set));
//	tuple_temp->SetLabel(nullptr); // ����� ����������� �������
//	tuple_temp->putTextOfFormula(nullptr); // ����� ����� �������
}


Tuple::Tuple(EntityVariable & ev1, EntityVariable & ev2, EntityVariable & set)
{
//	dobavka=TCHAR(' ');
    type = TUPLE;
    level = 0;
    feature = PERFORMED_FEATURE;    // "���������"
    freeVariables.push_back(new EntityVariable(ev1));
    freeVariables.push_back(new EntityVariable(ev2));
    freeVariables.push_back(new EntityVariable(set));
//	tuple_temp->SetLabel(nullptr); // ����� ����������� �������
//	tuple_temp->putTextOfFormula(nullptr); // ����� ����� �������
}

Tuple::Tuple(vector <EntityVariable *> * pev, EntityVariable & set)
{
//	dobavka=TCHAR(' ');
    type = TUPLE;
    level = 0;
    feature = PERFORMED_FEATURE;    // "���������"
    for(size_t i = 0; i < pev->size(); i++)
    {
        freeVariables.push_back(new EntityVariable(*pev->at(i)));
    }
    freeVariables.push_back(new EntityVariable(set));
//	tuple_temp->SetLabel(nullptr); // ����� ����������� �������
//	tuple_temp->putTextOfFormula(nullptr); // ����� ����� �������
}
//
// ����� ����� �������
//
void Tuple::SetTupleText( vector <EntityVariable *> * depending, tstring * ptvars)
{
    vector <EntityVariable *> * fv = &freeVariables;
    tstring text_add1;
    if(ptvars != nullptr)
    {
        text_add1 = *ptvars;
    }
    else
    {
        size_t icount = 0;
        for ( size_t i = 0; i < (fv->size() - 1); i++ )
        {
            if ( icount > 0 )    // ���� ������ ��� ������ �� ����� ����������
                text_add1 += _T(" , ");    // ��������� ������� � ������������ ���������
            text_add1 += *(fv->at(i)->GetText());    // ��������� ����� ������� ����������
            icount++;
        }
    }
    text += _T("<Symbol=/left_tag> ");
    text += text_add1;
    text += _T(" <Symbol=/right_tag>");
    text += _T(" <Symbol=/in> ");
    text += *(fv->at(fv->size() - 1)->GetText()); // ��������� ����� ���������, �������� ����������� ������, ��������� ��� ��������� ��������� ����������
    if(depending != nullptr)
    {
        text += _T("( ");
        for ( size_t i = 0; i < depending->size(); i++ )
        {
            if(i > 0)
                text += _T(" , ");
            text += *(depending->at(i)->GetText());
        }
        text += _T(" )");
    }
}


Tuple::~Tuple(void)
{
//	dobavka=TCHAR(' ');
}


// ������� ���������, �������� �� ������ ��������� ������������ ����� ���������� ��� ��������� � �������������� ������� ������
//	(��������, � ������������ ���������)
bool isTextOfVariable(tstring & text)
{
    bool result = false;
    TCHAR allValues[] = { TCHAR('A'), TCHAR('B'), TCHAR('C'), TCHAR('D'), TCHAR('E'), TCHAR('F'), TCHAR('G'), TCHAR('H'), TCHAR('I'), TCHAR('J'), TCHAR('K'),
        TCHAR('L'), TCHAR('N'), TCHAR('O'), TCHAR('Q'), TCHAR('S'), TCHAR('T'), TCHAR('U'), TCHAR('V'), TCHAR('W'), TCHAR('X'), TCHAR('Y'), TCHAR('Z') ,
        TCHAR('a'), TCHAR('b'), TCHAR('c'), TCHAR('d'), TCHAR('e'), TCHAR('f'), TCHAR('g'), TCHAR('h'), TCHAR('i'), TCHAR('j'), TCHAR('k'),
        TCHAR('l'), TCHAR('m'), TCHAR('n'), TCHAR('o'), TCHAR('p'), TCHAR('q'), TCHAR('r'), TCHAR('s'), TCHAR('t'), TCHAR('u'), TCHAR('v'), TCHAR('w'),
        TCHAR('x'), TCHAR('y'), TCHAR('z') };
//	vector<TCHAR> allvalues(allValues);
    tstring perf_text = text;
    trimWhitespaces(&perf_text);
    if((perf_text.length() > 0) && (perf_text[0] == TCHAR('(')) && (perf_text[perf_text.length() - 1] == TCHAR(')')) )
    {
        result = false;
    }
    else
    {
        TCHAR c = perf_text[0];
        for(int i = 0; i < sizeof(allValues); i++)
        {
            if(allValues[i] == c)
            {
                result = true;
                break;
            }
        }
        if(result && perf_text.length())
        {
            perf_text = perf_text.substr(1);
            tstring low_index = _T("<Symbol=/low>");
            result = false;
            size_t found_pos = perf_text.find(low_index, 0);
            size_t must_be_loc = 0;
            while(found_pos == must_be_loc)
            {
                result = true;
                must_be_loc += low_index.length() + 1;
                found_pos = perf_text.find(low_index, must_be_loc);
                if(must_be_loc == perf_text.length() )
                    break;
                if(found_pos == tstring::npos)
                {
                    result = false;
                    break;
                }
                result = false;
            }
        }
    }
    return result;
}

// ������������� �������� ��� ��� ���� REPLACE_VARIABLE, ��������� ��� ������� ���������, ��� �������, ��������� ����� �� ������ ������ �������� ���������
void EntityBase::SetReplacing(EntityBase * base_, EntityVariable * initial_, EntityVariable * new_)
{
    type = REPLACE_VARIABLE;
    if(base_->getType() == REPLACE_VARIABLE)
    {
//		replaced_base = base_->getReplacedBase();
        replaced_base = base_;
        initial_variable = new EntityVariable(*initial_);
//		initial_variable = new EntityVariable(*base_->getInitialVariable());
    }
    else
    {
        replaced_base = base_;
        initial_variable = new EntityVariable(*initial_);
    }
    new_variable = new EntityVariable(*new_);
    vector <EntityVariable *> * pev = replaced_base->getFreeVariables();
    // ������ ������ ��������� ����������
    for(size_t i = 0; i < pev->size(); i++)
    {
        if( pev->at(i)->compare(*initial_variable))
        {
            EntityVariable * pev_new = new EntityVariable(*new_variable);
            freeVariables.push_back(pev_new);
        }
        else
        {
            EntityVariable * pev_new =	new EntityVariable(*pev->at(i));
            freeVariables.push_back(pev_new);
        }
    }
    if(base_->isSet())
    {
        FormulaSet * pf_set = (FormulaSet*)this;
//		NamingVariable * pnaming_old = ((FormulaSet*)base_)->getNaming();
//		NamingVariable * pnaming_new = ((FormulaSet*)this)->getNaming();
        EntityVariable * pnaming_old = ((FormulaSet*)base_)->getNaming();
        EntityVariable * pnaming_new = ((FormulaSet*)this)->getNaming();
        if(pnaming_old != nullptr)
        {
            if(pnaming_new == nullptr)
            {
//				pnaming_new = new NamingVariable(*pnaming_old);
                pnaming_new = new EntityVariable(*pnaming_old);
//				pnaming_new->SetRedefinition(tstring(_T("")));
                pnaming_new->SetRedefinition((this->getText()));
                pf_set->setNaming(pnaming_new);
            }
        }
    }
    else if(base_->isFormula())
    {
        Formula * pf = (Formula *)this;
        Formula * pf_base = (Formula * )base_;
        pf->setFeature(pf_base->getFeature());
    }
    // ��������� ����� �� ������ ������ �������� ������� ����� ������ ����������� ����������� �� �����
//	tstring text1 = *replaced_base->getInitialText();
    tstring text1 = (replaced_base->getText());
    tstring new_text = *(new_variable->GetText());
    // ���� ���������� ���� �������������� �� ������ ��� �� ����� ���������� � ��������������� �� ��������� � �������, �� ������� � � ������
    if(!isTextOfVariable(new_text))
        new_text = _T("(") + new_text + _T(")");
    tstring initial_part = *(initial_variable->GetText());
    tstring low_index = _T("<Symbol=/low>");
    size_t found_pos = text1.find(initial_part);
    while(found_pos != tstring::npos)
    {
        // ��������, ���� �� ����� �� ���������� ����������� ����������� ������� �������, ���� ����, �� �� ������� ������
        // ��� ������� � ���, ����� �� �������� �11, ��������, ����� ����� �������� X1
        size_t new_pos = found_pos + initial_part.length();
        size_t new_pos1 = text1.find(low_index.data(), new_pos, low_index.length());
        if( (new_pos1 == tstring::npos) || (new_pos1 != new_pos) )
        {
            text1.replace(found_pos, initial_part.length(), new_text);
            found_pos = text1.find(initial_part, found_pos + new_text.length());
//			found_pos = text1.find(initial_part, found_pos + new_variable->GetText()->length());
        }
        else
            found_pos = text1.find(initial_part, found_pos + initial_part.length());
    }
    text = text1;
    if(base_->isSet())
    {
        FormulaSet * pf_set = (FormulaSet*)this;
        EntityVariable * pnaming_new = ((FormulaSet*)this)->getNaming();
        if(pnaming_new != nullptr)
        {
            tstring redefinition = this->getText();
            trimWhitespaces(&redefinition);
            if( (redefinition.length() > 0) && (redefinition[0] == TCHAR('(') ) )
                redefinition = redefinition.substr(1, redefinition.length() - 1);
            if( (redefinition.length() > 0) && (redefinition[redefinition.length() - 1] == TCHAR(')') ) )
                redefinition = redefinition.substr(0, redefinition.length() - 1);
            trimWhitespaces(&redefinition);
            pnaming_new->SetRedefinition(redefinition);
        }
    }
    // ���� �������������� ������ �������������, ��������� ��� ��������������� �� �� ������, ��� � ��� ������
    if(replaced_base->isRedefined())
    {
        // ��������� ����� ��������������� �� ������ ��������������� �������� ������� ����� ������ ����������� ����������� �� �����
        tstring text1 = *replaced_base->getRedefinedText();
        tstring initial_part = *(initial_variable->GetText());
        tstring new_text = *(new_variable->GetText());
        // ���� ���������� ���� �������������� �� ������ ��� �� ����� ���������� � ��������������� �� ��������� � �������, �� ������� � � ������
        if(!isTextOfVariable(new_text))
            new_text = _T("(") + new_text + _T(")");
        tstring low_index = _T("<Symbol=/low>");
        size_t found_pos = text1.find(initial_part);
        while(found_pos != tstring::npos)
        {
            // ��������, ���� �� ����� �� ���������� ����������� ����������� ������� �������, ���� ����, �� �� ������� ������
            // ��� ������� � ���, ����� �� �������� �11, ��������, ����� ����� �������� X1
            size_t new_pos = found_pos + initial_part.length();
            size_t new_pos1 = text1.find(low_index.data(), new_pos, low_index.length());
            if( (new_pos1 == tstring::npos) || (new_pos1 != new_pos) )
            {
//				text1.replace(found_pos, initial_part.length(), *(new_variable->GetText()));
//				found_pos = text1.find(initial_part, found_pos + new_variable->GetText()->length());
                text1.replace(found_pos, initial_part.length(), new_text);
                found_pos = text1.find(initial_part, found_pos + new_text.length());
            }
            else
                found_pos = text1.find(initial_part, found_pos + initial_part.length());
        }
        SetText(text1.data());
    }
};

// �������� ��������� ���� �������� EntityVariable ��� �������� ��������� �� ���. ������������ � binary_search
bool myentity_compare(EntityVariable * ev, EntityVariable * evcomp)
{
    return (!ev->compare(*evcomp));
}


EntityBaseType EntityBase::getReplacedType()
{
    if((type != FORMULA_SET) && isRedefined())
        return ATOMIC_FORMULA;
    else
    {
        EntityBase * pbase = this;
        EntityBaseType replaced_type = type;
        while(replaced_type == REPLACE_VARIABLE)
        {
            pbase = pbase->getReplacedBase();
            replaced_type = pbase->getType();
        }
        return replaced_type;
    }
};


// ����������, �������� �� ������ ������ ������ ������, ����������� � ������ ��������� ����������, ���������� ������ ��������� �� �������������� ���������
// ���������� � ����� �������� � ������, ���� ������ � ������, nullptr � 0, ���� �� ������
SetGroup EntityBase::isPartOfSetGroup(vector <EntityBase *> * pentities)
{
    int count = 0;
    EntityBase * peb = nullptr;
    int pos = 0;
    if(find(pentities->begin(), pentities->end(), this) != pentities->end()) // ���� ������ ������ ���������� � �����
    {
        EntityBaseType curr_type = this->getType();
        EntityBase * test_base = this;
        if(curr_type == REPLACE_VARIABLE)
        {
//			test_base = this->getReplacedBase();
        }
        for(size_t i = 0; i < pentities->size(); i++)
        {
            // ���������� ���������� ����� ������� �������
            if(test_base == pentities->at(i))
            {
                pos = i;
                break;
            }
        }
        if(curr_type == REPLACE_VARIABLE)
        {
            curr_type = this->getReplacedBase()->getReplacedType();
        }
        switch(curr_type)
        {
        case FORMULA_SET:
            {
                peb = this;
                count = 1;
                if(pentities->size() > (pos + 1)) /// ��������� �� ������� ��������� ��������� ��������� ��������������
                {
                    EntityBase * pebplus1 = pentities->at(pos + 1);
                    if( (pebplus1->getType() == BELONGING_PREDICATE) ||
                        ( (pebplus1->getType() == REPLACE_VARIABLE) && (pebplus1->getReplacedBase()->getReplacedType() == BELONGING_PREDICATE) ) )
                    {
                        count++;
                        pos++;
                    }
                }
                if(pentities->size() > (pos + 2)) /// ���� � ����� ��������� ����������, ����� �������� ��� � ���� ������-������������
                {
                    EntityBase * pebplus1 = pentities->at(pos + 1);
                    EntityBase * pebplus2 = pentities->at(pos + 2);
                    if(((pebplus1->getType() == TUPLE) && (pebplus2->getType() == SUBSET)) ||
                        ( (pebplus1->getType() == REPLACE_VARIABLE) && (pebplus1->getReplacedBase()->getReplacedType() == TUPLE) &&
                        (pebplus2->getType() == REPLACE_VARIABLE) && (pebplus2->getReplacedBase()->getReplacedType() == SUBSET) ) )
                    {
                        count += 2;
                    }
                }

                break;
            }
        case BELONGING_PREDICATE:
            {
                if(pos > 0)
                {
                    EntityBase * pebminus1 = pentities->at(pos - 1);
                    if( (pebminus1->getType() == FORMULA_SET) ||
                        ( (pebminus1->getType() == REPLACE_VARIABLE) && (pebminus1->getReplacedBase()->getReplacedType() == FORMULA_SET ) ) ) // ���� ���������� ������ - ��������� ����������
                    {
                        peb = pebminus1;
                        if(pentities->size() > (pos + 2)) // ���� ���� ��� ���� �� ��� ������� � �����, �� �������� �� ������� ������� � ������������
                        {
                            EntityBase * pebplus1 = pentities->at(pos + 1);
                            EntityBase * pebplus2 = pentities->at(pos + 2);
                            if( ((pentities->at(pos + 1)->getType() == TUPLE) && (pentities->at(pos + 2)->getType() == SUBSET)) ||
                                ( (pebplus1->getType() == REPLACE_VARIABLE) && (pebplus1->getReplacedBase()->getReplacedType() == TUPLE) &&
                                (pebplus2->getType() == REPLACE_VARIABLE) && (pebplus2->getReplacedBase()->getReplacedType() == SUBSET)) )
                            {
                                count = 4;
                            }
                        }
                        else
                            count = 2;
                    }
                }
                break;
            }
        case TUPLE:
            {
                if(pentities->size() > (pos + 1))
                {
                    EntityBase * pebplus1 = pentities->at(pos + 1);
                    if( (pebplus1->getType() == SUBSET) || ( (pebplus1->getType() == REPLACE_VARIABLE) && (pebplus1->getReplacedBase()->getReplacedType() == SUBSET) ) )
                        // ��� ������� ����������� ����������� ������� - ������������
                    {
                        EntityBase * pebminus1 = pentities->at(pos - 1);
                        EntityBase * pebminus2 = pentities->at(pos - 2);
                        if( ((pebminus1->getType() == BELONGING_PREDICATE) && (pebminus2->getType() == FORMULA_SET)) ||
                            ( (pebminus1->getType() == REPLACE_VARIABLE) && (pebminus1->getReplacedBase()->getReplacedType() == BELONGING_PREDICATE) &&
                                (pebminus2->getType() == REPLACE_VARIABLE) && (pebminus2->getReplacedBase()->getReplacedType() == FORMULA_SET) ) ) // ���� ������ �����
                        {
                            peb = pebminus2;
                            count = 4;
                        }
                        else if(pebminus1->getType() == FORMULA_SET) // ������ ��� ��������� ��������������
                        {
                            peb = pebminus1;
                            count = 3;
                        }
                    }
                }
                break;
            }
        case SUBSET:
            {
                if(pos > 3) // ����� ���� � ������, ����������, ��� �������, ��� ����� ������ ����� ������������� � ���� ��������� �������
                {
                    EntityBase * pebminus1 = pentities->at(pos - 1);
                    EntityBase * pebminus2 = pentities->at(pos - 2);
                    EntityBase * pebminus3 = pentities->at(pos - 3);
                    if( (pebminus1->getType() == TUPLE) ||
                        ( (pebminus1->getType() == REPLACE_VARIABLE) && (pebminus1->getReplacedBase()->getReplacedType() == TUPLE) ) )
                        // �������������� � ������ ����������� ������
                    {
                        if( ((pebminus2->getType() == BELONGING_PREDICATE) && (pebminus3->getType() == FORMULA_SET)) ||
                            ( (pebminus2->getType() == REPLACE_VARIABLE) && (pebminus2->getReplacedBase()->getReplacedType() == BELONGING_PREDICATE) &&
                            (pebminus3->getType() == REPLACE_VARIABLE) && (pebminus3->getReplacedBase()->getReplacedType() == FORMULA_SET) ) ) // ���� ������ �����
                        {
                            peb = pebminus3;
                            count = 4;
                        }
                        else if( (pebminus2->getType() == FORMULA_SET) ||
                            (pebminus2->getType() == REPLACE_VARIABLE) && (pebminus2->getReplacedBase()->getReplacedType() == FORMULA_SET) )
                            // ��� ��������� ��������������
                        {
                            peb = pebminus2;
                            count = 3;
                        }
                    }
                }
                break;
            }
        }
    }
    SetGroup se(peb, count);
    return se;
}


// ������� ���� � �����, ����������� �� ���������� c ����� ������������ � ��������, ��������� true, ���� �������
bool isExistVariable(tstring & symbol, tstring & index, vector <EntityBase *> * entities)
{
    EntityVariable * psubset = nullptr;
    psubset =new EntityVariable(symbol, index, VARIABLE);
    bool foundEV = false;
    // �������� ����� �� ��, ���������� �� � ��� ��� ��������� ����������
    for (size_t i = 0; i < entities->size(); i++) // ������� ���� ��������� ���������
    {
        bool toProccess = false;
        EntityBase * base = entities->at(i);     // ��������� �� ��������� ��������
        // �������� �� ���������� ����������� ������������ � ����� ��������� ���������� ��� ��������� �������
        vector <EntityVariable *> * fv_base = base->getFreeVariables();
        for (size_t i1 = 0; i1 < fv_base->size(); i1++)    // ������� �� ���� ��������� ���������� ��������� ��������
        {
            EntityVariable * pev = fv_base->at(i1);
            if(pev->compare(*psubset))
            {
                foundEV = true;
                break;
            }
        }
        if(foundEV)
            break;
    }
    if(psubset != nullptr)
        delete psubset;
    return foundEV;
}


// ������� ���� � �����, ����������� �� �������������� ��������� ���������� c ����� ������������ � ��������, ��������� true, ���� �������
bool isExistNaming(tstring & symbol, tstring & index, vector <EntityBase *> * entities)
{
    EntityVariable * psubset = nullptr;
    psubset =new EntityVariable(symbol, index, VARIABLE);
    bool foundEV = false;
    // �������� ����� �� ��, ���������� �� � ��� ��� ��������� ����������
    for (size_t i = 0; i < entities->size(); i++) // ������� ���� ��������� ���������
    {
        bool toProccess = false;
        EntityBase * base = entities->at(i);     // ��������� �� ��������� ��������
        // �������� �� �� ���� ������ ������������ � ��������� ����������
        if(!foundEV && base->isSet() && ( ((FormulaSet *)base)->getNaming() != nullptr))
        {
            EntityVariable * pname = ((FormulaSet *)base)->getNaming();
            if(pname->compare(*psubset))
            {
                foundEV = true;
                break;
            }
        }
    }
    if(psubset != nullptr)
        delete psubset;
    return foundEV;
}


// ������� ���� � �����, ����������� �� �������������� ��������� ���������� c ����� ������������ � ��������, ��������� ��������� �� ����, ���� �������
// � nullptr ���� ����� ��������� ���������� �� �������
FormulaSet * isExistFormulaSet(tstring & symbol, tstring & index, vector <EntityBase *> * entities)
{
    EntityVariable * psubset = nullptr;
    psubset =new EntityVariable(symbol, index, VARIABLE);
    FormulaSet * foundEV = nullptr;
    // �������� ����� �� ��, ���������� �� � ��� ��� ��������� ����������
    for (size_t i = 0; i < entities->size(); i++) // ������� ���� ��������� ���������
    {
        bool toProccess = false;
        EntityBase * base = entities->at(i);     // ��������� �� ��������� ��������
        // �������� �� �� ���� ������ ������������ � ��������� ����������
        if(!foundEV && base->isSet() && ( ((FormulaSet *)base)->getNaming() != nullptr))
        {
            EntityVariable * pname = ((FormulaSet *)base)->getNaming();
            if(pname->compare(*psubset))
            {
                foundEV = (FormulaSet *)base;
                break;
            }
        }
    }
    if(psubset != nullptr)
        delete psubset;
    return foundEV;
}



/*
NamingVariable::~NamingVariable(void)
{

}

NamingVariable::NamingVariable(EntityVariable & ev)
{
    VariableType type_ = ev.GetType();
    SetType(type_);
    SetLabel(ev.GetLabel());
    SetIndex(ev.GetIndex());
    SetText();
    Level * pl = (Level *)&ev;
    SetLevel(pl->GetLevel());
    SetRedefinition(ev.GetRedefinition());
}
*/
