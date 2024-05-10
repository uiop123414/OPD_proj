//#include "StdAfx.h"
#include "Operation.h"
#include "Formula.h"


template<EntityBaseType Type> Operation<Type>::Operation(void)
{
}


template<EntityBaseType Type> Operation<Type>::~Operation(void)
{
}


//
// �������� �� �������������� ���� ��� ������ �� ��������������� "�"  A & (B & C) = (A & B) & C
//
bool IsAssocciativeIdentity(EntityBaseType ent_bt, const Formula& first_1, const Formula& first_2, const Formula& second_1, const Formula& second_2)
{
    bool result = false;
    Formula * pfirst_1 = const_cast<Formula *>(&first_1);
    Formula * pfirst_2 = const_cast<Formula *>(&first_2);
    Formula * psecond_1 = const_cast<Formula *>(&second_1);
    Formula * psecond_2 = const_cast<Formula *>(&second_2);
    if( ( ent_bt == ent_bt ) || ( ent_bt == ent_bt ) )
    {
        // ������ ������� ���� ��������� �������, ����� �� ���� ������� �� ����� ���� �� ����������� ����� ������� �� ������.

        // �������, ���������� �� � ���� ������� ������ �������� ������ ������������ ������� � ������ �������� ������ ������������
        // ������� ����� ����������� "�" ������
        if( ( pfirst_2->getType() == ent_bt ) && (  psecond_1->getType() == ent_bt ) )
        {
            //
            if( ( pfirst_2->getNumberOfParents() == 2 ) && (  psecond_1->getNumberOfParents() == 2 ) )    // ���������� ��������
            {
                // �������� ��������� �� ��������� ������� �������� ������ ������������ ������� � ������� �������� ������ ������������ �������
                Formula * first_2_1 = get<0>(* pfirst_2->getParentLink(0) );
                Formula * first_2_2 = get<0>(* pfirst_2->getParentLink(1) ) ;
                Formula * second_1_1 = get<0>(* psecond_1->getParentLink(0) );
                Formula * second_1_2 = get<0>(* psecond_1->getParentLink(1) );
                // ��������� ���������������, ������������� ��� ��������� ������������ ��� ����� ������
                if ( ( ( first_1 == *second_1_1 ) && ( *first_2_1 == *second_1_2 ) && (*first_2_2 == second_2 ) ) ||
                    ( ( first_1 == *second_1_2 ) && ( *first_2_1 == *second_1_1 ) && (*first_2_2 == second_2 ) ) ||
                    ( ( first_1 == *second_1_2 ) && ( *first_2_1 == second_2 ) && (*first_2_2 == *second_1_1 ) ) ||
                    ( ( first_1 == *second_1_1 ) && ( *first_2_1 == second_2 ) && (*first_2_2 == *second_1_2 ) ) )
                        return true;
            }
        }
        // ��� �������, ���������� �� � ���� ������� ������ �������� ������ ������������ ������� � ������ �������� ������ ������������
        // ������� ����� ����������� "�" ������.
        if( ( pfirst_1->getType() == ent_bt ) && ( psecond_1->getType() == ent_bt ) )
        {
            if( ( pfirst_1->getNumberOfParents() == 2 ) && ( psecond_1->getNumberOfParents() == 2 ) )    // ���������� ��������
            {
                // �������� ��������� �� ��������� ������� �������� ������ ������������ ������� � ������� �������� ������ ������������ �������
                Formula * first_1_1 = get<0>(* pfirst_1->getParentLink(0) );
                Formula * first_1_2 = get<0>(* pfirst_1->getParentLink(1) ) ;
                Formula * second_1_1 = get<0>(* psecond_1->getParentLink(0) );
                Formula * second_1_2 = get<0>(* psecond_1->getParentLink(1) );
                // ��������� ���������������, ������������� ��� ��������� ������������ ��� ����� ������
                if ( ( ( first_2 == *second_1_1 ) && ( *first_1_1 == *second_1_2 ) && (*first_1_2 == second_2 ) ) ||
                    ( ( first_2 == *second_1_1 ) && ( *first_1_1 == second_2 ) && (*first_1_2 == *second_1_2 ) ) ||
                    ( ( first_2 == *second_1_2 ) && ( *first_1_1 == *second_1_1 ) && (*first_1_2 == second_2 ) ) ||
                    ( ( first_2 == *second_1_2 ) && ( *first_1_1 == second_2 ) && (*first_1_2 == *second_1_1 ) ) )
                        return true;
            }
        }
        // ��� �������, ���������� �� � ���� ������� ������ �������� ������ ������������ ������� � ������ �������� ������ ������������
        // ������� ����� ����������� "�" ������.
        if( ( pfirst_1->getType() == ent_bt ) && ( psecond_2->getType() == ent_bt ) )
        {
            if( ( pfirst_1->getNumberOfParents() == 2 ) && ( psecond_2->getNumberOfParents() == 2 ) )    // ���������� ��������
            {
                // �������� ��������� �� ��������� ������� �������� ������ ������������ ������� � ������� �������� ������ ������������ �������
                Formula * first_1_1 = get<0>(* pfirst_1->getParentLink(0) );
                Formula * first_1_2 = get<0>(* pfirst_1->getParentLink(1) ) ;
                Formula * second_2_1 = get<0>(* psecond_2->getParentLink(0) );
                Formula * second_2_2 = get<0>(* psecond_2->getParentLink(1) );
                // ��������� ���������������, ������������� ��� ��������� ������������ ��� ����� ������
                if ( ( ( first_2 == *second_2_1 ) && ( *first_1_1 == *second_2_2 ) && (*first_1_2 == second_1 ) ) ||
                    ( ( first_2 == *second_2_1 ) && ( *first_1_1 == second_1 ) && (*first_1_2 == *second_2_2 ) ) ||
                    ( ( first_2 == *second_2_2 ) && ( *first_1_1 == *second_2_1 ) && (*first_1_2 == second_1 ) ) ||
                    ( ( first_2 == *second_2_2 ) && ( *first_1_1 == second_1 ) && (*first_1_2 == *second_2_1 ) ) )
                        return true;
            }
        }
        // ��� �������, ���������� �� � ���� ������� ������ �������� ������ ������������ ������� � ������ �������� ������ ������������
        // ������� ����� ����������� "�" ������
        if( ( pfirst_2->getType() == ent_bt ) && ( psecond_2->getType() == ent_bt ) )
        {
            if( ( pfirst_2->getNumberOfParents() == 2 ) && ( psecond_2->getNumberOfParents() == 2 ) )    // ���������� ��������
            {
                // �������� ��������� �� ��������� ������� �������� ������ ������������ ������� � ������� �������� ������ ������������ �������
                Formula * first_2_1 = get<0>(* pfirst_2->getParentLink(0) );
                Formula * first_2_2 = get<0>(* pfirst_2->getParentLink(1) ) ;
                Formula * second_2_1 = get<0>(* psecond_2->getParentLink(0) );
                Formula * second_2_2 = get<0>(* psecond_2->getParentLink(1) );
                // ��������� ���������������, ������������� ��� ��������� ������������ ��� ����� ������
                if ( ( ( first_1 == *second_2_1 ) && ( *first_2_1 == *second_2_2 ) && (*first_2_2 == second_1 ) ) ||
                    ( ( first_1 == *second_2_2 ) && ( *first_2_1 == *second_2_1 ) && (*first_2_2 == second_1 ) ) ||
                    ( ( first_1 == *second_2_2 ) && ( *first_2_1 == second_1 ) && (*first_2_2 == *second_2_1 ) ) ||
                    ( ( first_1 == *second_2_1 ) && ( *first_2_1 == second_1 ) && (*first_2_2 == *second_2_2 ) ) )
                        return true;
            }
        }
    }
    return result;
}

//
//  ������� ��������� �������������� �������� ������� ������ ����������, � ������ �������������� ���������� ��������� �� ����� ������� �������, ����� nullptr
//  A & (A V B) = A
//
Formula * IsFirstAbsorbtionLawIdentity(const Formula& firstOf, const Formula& secondOf)
{
    Formula * formula = nullptr;
    Formula * first = const_cast<Formula *>(&firstOf);
    Formula * second = const_cast<Formula *>(&secondOf);
    for(int i = 0; i < 2; i++)
    {
        if( i == 1 )    // �� ������ ���� �������� ����� ���������� �������, ����� ������ ��������� ������������
        {
            first = const_cast<Formula *>(&secondOf);
            second = const_cast<Formula *>(&firstOf);
        }
        if( (first->getType() == AND_OPERATION ) && (first->getNumberOfParents() == 2) )   // ���� ������ ������� ���������� ������������ "�"
        {
            // ������� ������������ ������� ��� ������� firstOf
            Formula * first_1 = get<0>(* first->getParentLink(0) );
            Formula * first_2 = get<0>(* first->getParentLink(1) );
            if( *first_1 == *second )    // ���� ������ �������� ������ ������� ��������� �� ������
            {
                if( ( first_2->getType() == OR_OPERATION ) && ( first_2->getNumberOfParents() == 2 ) )
                {
                    if( ( *get<0>( *first_2->getParentLink(0) ) == *second ) ||
                        ( *get<0>( *first_2->getParentLink(1) ) == *second ) )
                            formula = second;
                }
            }
            else if( *first_2 == *second )    // ���� ������ �������� ������ ������� ��������� �� ������
            {
                if( ( first_1->getType() == OR_OPERATION ) && ( first_1->getNumberOfParents() == 2 ) )
                {
                    if( ( *get<0>( *first_1->getParentLink(0) ) == *second ) ||
                        ( *get<0>( *first_1->getParentLink(1) ) == *second ) )
                            formula = second;
                }
            }
        }
        if(formula)
            break;
    }
    return formula;
}


//
//  ������� ��������� �������������� �������� ������� ������ ����������, � ������ �������������� ���������� ��������� �� ����� ������� �������, ����� nullptr
//  A V ( A & B ) = A
//
Formula * IsSecondAbsorbtionLawIdentity(const Formula& firstOf, const Formula& secondOf)
{
    Formula * formula = nullptr;
    Formula * first = const_cast<Formula *>(&firstOf);
    Formula * second = const_cast<Formula *>(&secondOf);
    for(int i = 0; i < 2; i++)
    {
        if( i == 1 )    // �� ������ ���� �������� ����� ���������� �������, ����� ������ ��������� ������������
        {
            first = const_cast<Formula *>(&secondOf);
            second = const_cast<Formula *>(&firstOf);
        }
        if( (first->getType() == OR_OPERATION ) && (first->getNumberOfParents() == 2) )   // ���� ������ ������� ���������� ������������ "���"
        {
            // ������� ������������ ������� ��� ������� firstOf
            Formula * first_1 = get<0>(* first->getParentLink(0) );
            Formula * first_2 = get<0>(* first->getParentLink(1) );
            if( *first_1 == *second )    // ���� ������ �������� ������ ������� ��������� �� ������
            {
                if( ( first_2->getType() == AND_OPERATION ) && ( first_2->getNumberOfParents() == 2 ) )
                {
                    if( ( *get<0>( *first_2->getParentLink(0) ) == *second ) ||
                        ( *get<0>( *first_2->getParentLink(1) ) == *second ) )
                            formula = second;
                }
            }
            else if( *first_2 == *second )    // ���� ������ �������� ������ ������� ��������� �� ������
            {
                if( ( first_1->getType() == AND_OPERATION ) && ( first_1->getNumberOfParents() == 2 ) )
                {
                    if( ( *get<0>( *first_1->getParentLink(0) ) == *second ) ||
                        ( *get<0>( *first_1->getParentLink(1) ) == *second ) )
                            formula = second;
                }
            }
        }
        if(formula)
            break;
    }
    return formula;
}


//
//  ������� ��������� �������������� ������������� � ������ �������� ���������, � ������ �������������� ����� ������ ���������� ��������� ��
// ������� � ����� ������� �����, ����� nullptr
//  not ( not A ) = A
//
Formula * IsDoubleNeativeIdentity(const Formula& firstOf, const Formula& secondOf)
{
    Formula * formula = nullptr;
    Formula * first = const_cast<Formula *>(&firstOf);
    Formula * second = const_cast<Formula *>(&secondOf);
    for(int i = 0; i < 2; i++)
    {
        if( i == 1 )    // �� ������ ���� �������� ����� ���������� �������, ����� ������ ��������� ������������
        {
            first = const_cast<Formula *>(&secondOf);
            second = const_cast<Formula *>(&firstOf);
        }
        if( (first->getType() == NEGATIVE_OPERATION ) && (first->getNumberOfParents() == 1) )   // ���� ������ ������� ���������� ��������� ���������
        {
            // ������� ������������ ������� ��� ������� firstOf
            Formula * first_1 = get<0>(* first->getParentLink(0) );

            if( (first_1->getType() == NEGATIVE_OPERATION ) && (first->getNumberOfParents() == 1) )    // ���� �������� ������� ����� ��������� ��������� ���������
            {
                if( * get<0>( *first_1->getParentLink(0) ) == *second )
                    formula = second;
            }
        }
        if(formula)
            break;
    }
    return formula;
}


//
//  ������� ��������� �������������� �� ������� ������ �������, � ������ �������������� ����� ������ ���������� ��������� ��
// ������� � ����� ������� �����, ����� nullptr
//  ( A & B ) = not A V not B
//
Formula * IsFirstMorganLawIdentity(const Formula& firstOf, const Formula& secondOf)
{
    Formula * formula = nullptr;
    Formula * first = const_cast<Formula *>(&firstOf);
    Formula * second = const_cast<Formula *>(&secondOf);
    for(int i = 0; i < 2; i++)
    {
        if( i == 1 )    // �� ������ ���� �������� ����� ���������� �������, ����� ������ ��������� ������������
        {
            first = const_cast<Formula *>(&secondOf);
            second = const_cast<Formula *>(&firstOf);
        }
        if( (first->getType() == AND_OPERATION ) && (first->getNumberOfParents() == 2) )   // ���� ������ ������� ���������� ������������ "�"
        {
            // ������� ������������ ������� ��� ������� first
            Formula * first_1 = get<0>(* first->getParentLink(0) );
            Formula * first_2 = get<0>(* first->getParentLink(1) );

            if( (first_1->getType() == OR_OPERATION ) && (first->getNumberOfParents() == 2) )    // ���� ������ ������� ���������� ��������� ������������ "���"
            {
                // ������� ������������ ������� ��� ������� first
                Formula * second_1 = get<0>(* second->getParentLink(0) );
                Formula * second_2 = get<0>(* second->getParentLink(1) );
                if( ( second_1->getType() == NEGATIVE_OPERATION ) && (second_2->getType() == NEGATIVE_OPERATION ) )
                {
                    if ( ( *get<0>( *second_1->getParentLink(0) ) == *first_1 ) && ( *get<0>( *second_2->getParentLink(0) ) == *first_1 ) )
                        formula = first;
                }
            }
        }
        if(formula)
            break;
    }
    return formula;
}


//
//  ������� ��������� �������������� �� ������� ������ �������, � ������ �������������� ����� ������ ���������� ��������� ��
// ������� � ����� ������� �����, ����� nullptr
//  ( A V B ) = not A & not B
//
Formula * IsSecondMorganLawIdentity(const Formula& firstOf, const Formula& secondOf)
{
    Formula * formula = nullptr;
    Formula * first = const_cast<Formula *>(&firstOf);
    Formula * second = const_cast<Formula *>(&secondOf);
    for(int i = 0; i < 2; i++)
    {
        if( i == 1 )    // �� ������ ���� �������� ����� ���������� �������, ����� ������ ��������� ������������
        {
            first = const_cast<Formula *>(&secondOf);
            second = const_cast<Formula *>(&firstOf);
        }
        if( (first->getType() == OR_OPERATION ) && (first->getNumberOfParents() == 2) )   // ���� ������ ������� ���������� ������������ "�"
        {
            // ������� ������������ ������� ��� ������� first
            Formula * first_1 = get<0>(* first->getParentLink(0) );
            Formula * first_2 = get<0>(* first->getParentLink(1) );

//			if( (first_1->getType() == AND_OPERATION ) && (first->getNumberOfParents() == 2) )    // ���� ������ ������� ���������� ��������� ������������ "���"
            if( (second->getType() == AND_OPERATION ) && (second->getNumberOfParents() == 2) )    // ���� ������ ������� ���������� ��������� ������������ "���"
            {
                // ������� ������������ ������� ��� ������� first
                Formula * second_1 = get<0>(* second->getParentLink(0) );
                Formula * second_2 = get<0>(* second->getParentLink(1) );
                if( ( second_1->getType() == NEGATIVE_OPERATION ) && (second_2->getType() == NEGATIVE_OPERATION ) )
                {
                    if ( ( *get<0>( *second_1->getParentLink(0) ) == *first_1 ) && ( *get<0>( *second_2->getParentLink(0) ) == *first_1 ) )
                        formula = first;
                }
            }
        }
        if(formula)
            break;
    }
    return formula;
}


//
//  ������� ��������� �������������� ������������� � ������ ������� �����������, � ������ �������������� ����� ������ ���������� ��������� ��
// ������� � ����� ������� �����, ����� nullptr
//  A = ( A & B ) V ( A & not B )
//
Formula * IsFirstSplitFormulaIdentity(const Formula& firstOf, const Formula& secondOf)
{
    Formula * formula = nullptr;
    Formula * first = const_cast<Formula *>(&firstOf);
    Formula * second = const_cast<Formula *>(&secondOf);
    for(int i = 0; i < 2; i++)
    {
        if( i == 1 )    // �� ������ ���� �������� ����� ���������� �������, ����� ������ ��������� ������������
        {
            first = const_cast<Formula *>(&secondOf);
            second = const_cast<Formula *>(&firstOf);
        }
        if( (first->getType() == OR_OPERATION ) && (first->getNumberOfParents() == 2) )   // ���� ������ ������� ���������� ������������ "���"
        {
            // ������� ������������ ������� ��� ������� first
            Formula * first_1 = get<0>(* first->getParentLink(0) );
            Formula * first_2 = get<0>(* first->getParentLink(1) );
            // ���� ��� �������� ������ ������� ��������� ������������ "�" ������
            if( (first_1->getType() == AND_OPERATION ) && (first_1->getNumberOfParents() == 2) &&
                (first_2->getType() == AND_OPERATION ) && (first_2->getNumberOfParents() == 2) )
            {
                Formula * firstOf_1 = first_1;
                Formula * firstOf_2 = first_2;
                for( int j = 0; j < 2; j++)
                {
                    if(j == 1)
                    {
                        firstOf_1 = first_2;
                        firstOf_2 = first_1;
                    }
                    Formula * first_1_1 = get<0>( *( firstOf_1->getParentLink(0) ) );
                    Formula * first_1_2 = get<0>( *( firstOf_1->getParentLink(1) ) );
                    Formula * first_2_1 = get<0>( *( firstOf_2->getParentLink(0) ) );
                    Formula * first_2_2 = get<0>( *( firstOf_2->getParentLink(1) ) );
                    if ( *first_1_1 == *first_2_1)
                    {
                        if( ( first_2_2->getType() == NEGATIVE_OPERATION ) && ( *get<0>( *first_2_2->getParentLink(0) ) == *first_1_2 ) )
                            if ( *first_1_1 == *second)
                                formula = second;
                    }
                    else if( *first_1_1 == *first_2_2)
                    {
                        if( ( first_2_1->getType() == NEGATIVE_OPERATION ) && ( *get<0>( *first_2_1->getParentLink(0) ) == *first_1_2 ) )
                            if ( *first_1_1 == *second)
                                formula = second;
                    }
                    if(formula)
                        break;
                }
            }
        }
        if(formula)
            break;
    }
    return formula;
}


//
//  ������� ��������� �������������� ������������� �� ������ ������� �����������, � ������ �������������� ����� ������ ���������� ��������� ��
// ������� � ����� ������� �����, ����� nullptr
//  A = ( A V B ) & ( A V not B )
//
Formula * IsSecondSplitFormulaIdentity(const Formula& firstOf, const Formula& secondOf)
{
    Formula * formula = nullptr;
    Formula * first = const_cast<Formula *>(&firstOf);
    Formula * second = const_cast<Formula *>(&secondOf);
    for(int i = 0; i < 2; i++)
    {
        if( i == 1 )    // �� ������ ���� �������� ����� ���������� �������, ����� ������ ��������� ������������
        {
            first = const_cast<Formula *>(&secondOf);
            second = const_cast<Formula *>(&firstOf);
        }
        if( (first->getType() == AND_OPERATION ) && (first->getNumberOfParents() == 2) )   // ���� ������ ������� ���������� ������������ "���"
        {
            // ������� ������������ ������� ��� ������� first
            Formula * first_1 = get<0>(* first->getParentLink(0) );
            Formula * first_2 = get<0>(* first->getParentLink(1) );
            // ���� ��� �������� ������ ������� ��������� ������������ "�" ������
            if( (first_1->getType() == OR_OPERATION ) && (first_1->getNumberOfParents() == 2) &&
                (first_2->getType() == OR_OPERATION ) && (first_2->getNumberOfParents() == 2) )
            {
                Formula * firstOf_1 = first_1;
                Formula * firstOf_2 = first_2;
                for( int j = 0; j < 2; j++)
                {
                    if(j == 1)
                    {
                        firstOf_1 = first_2;
                        firstOf_2 = first_1;
                    }
                    Formula * first_1_1 = get<0>( *(firstOf_1->getParentLink(0) ) );
                    Formula * first_1_2 = get<0>( *(firstOf_1->getParentLink(1) ) );
                    Formula * first_2_1 = get<0>( *(firstOf_2->getParentLink(0) ) );
                    Formula * first_2_2 = get<0>( *(firstOf_2->getParentLink(1) ) );
                    if ( *first_1_1 == *first_2_1)
                    {
                        if( ( first_2_2->getType() == NEGATIVE_OPERATION ) && ( *get<0>( *first_2_2->getParentLink(0) ) == *first_1_2 ) )
                            if ( *first_1_1 == *second)
                                formula = second;
                    }
                    else if( *first_1_1 == *first_2_2)
                    {
                        if( ( first_2_1->getType() == NEGATIVE_OPERATION ) && ( *get<0>( *first_2_1->getParentLink(0) ) == *first_1_2 ) )
                            if ( *first_1_1 == *second)
                                formula = second;
                    }
                    if(formula)
                        break;
                }
            }
        }
        if(formula)
            break;
    }
    return formula;
}


//
//  ������� ��������� �������������� ������������� � �������� �������� ����� �������� ��������� ��� ������� �� ��������� ����������, �� ������� �� �������,
//  � ������ �������������� ����� ������ ���������� ��������� �� ������� � ����� ������� �����, ����� nullptr
//  not ( K x ) A ( x ) = ( K x ) not A ( x )
//
Formula * IsMoveQuantifierThroughNegotiation(const Formula& firstOf, const Formula& secondOf)
{
    Formula * formula = nullptr;
    Formula * first = const_cast<Formula *>(&firstOf);
    Formula * second = const_cast<Formula *>(&secondOf);
    for(int i = 0; i < 2; i++)
    {
        if( i == 1 )    // �� ������ ���� �������� ����� ���������� �������, ����� ������ ��������� ������������
        {
            first = const_cast<Formula *>(&secondOf);
            second = const_cast<Formula *>(&firstOf);
        }
        if( first->isNegative() && second->isQuantifier() )
            // ���� ������ ������� ���������� ��������� ���������, � ������ ������������ ��������
        {
            // ������� ������������ ������� ��� �����
            Formula * first_1 = get<0>(* first->getParentLink(0) );
            Formula * second_1 = get<0>(* second->getParentLink(0) );
            EntityBaseType ent_bt = second->getType();
            if( first_1->isQuantifier() && (first->getType() != ent_bt ) && second_1->isNegative() )
            {
                // ������� "�����" (������������ ������� ��� ��������� )
                Formula * first_1_1 = get<0>( * (first_1->getParentLink(0) ) );
                Formula * second_1_1 = get<0>( *( second_1->getParentLink(0) ) );
                // ���������, ���������� �� ������� ������������ �������� �� ����� � ��� �� ����������
                EntityVariable * pev1 = get<1>(* second->getParentLink(0) );
                EntityVariable * pev2 = get<1>(* first_1->getParentLink(0) );
                if( ( *pev1 == *pev2 ) && ( *first_1_1 == *second_1_1 ) )    // ���� ���������� ����� (���� � �� ��) � "���������" ������� �����������
                {
                    formula = first;    // ��������� �������, ������������ � �������� ��� ����� ��������
                }
            }
            // ���� �������� ������� ��������� ����������� ��������
        }
        if(formula)
            break;
    }
    return formula;
}

//
//  ������� ������������ ��� ��������� ���������� �������� � ������� � ���������� ��������� �� ���������� �������, nullptr ���� �������
//
Formula * SwapTowUpperQuantifiers(Formula * formula)
{
    Formula * result = nullptr;
    if( formula->isQuantifier() )
    {
        EntityBaseType ent_bt = formula->getType();
        Formula * first_parent = get<0>( *(formula->getParentLink(0) ) );
        EntityVariable * pev1 = get<1>( *(formula->getParentLink(0) ) );
        if( first_parent->isQuantifier() && ( first_parent->getType() == ent_bt ) )
        {
            Formula * second_parent = get<0>( *(first_parent->getParentLink(0) ) );
            EntityVariable * pev2 = get<1>( *(first_parent->getParentLink(0) ) );
            Formula * created = second_parent->quantifierFormula(ent_bt, pev1);
            Formula * created_second = created->quantifierFormula(ent_bt, pev2);
            result = created_second;
        }
    }
    return result;
}


//
//  ������� ��������� �������������� ������������ ������������ ����������� ���������,
//  � ������ �������������� ����� ������ ���������� ��������� �� ������� � ����� ������� �����, ����� nullptr
//  K ( x ) K ( y ) A ( x , y ) = K ( y ) K ( x ) A ( x , y )
//
Formula *  IsReplaceSameQuantifiers(const Formula & firstOf, const Formula & secondOf)
{
    Formula * formula = nullptr;
    Formula * first = const_cast<Formula *>(&firstOf);
    Formula * second = const_cast<Formula *>(&secondOf);
    vector <EntityVariable *> vev1;
    vector <EntityVariable *> vev2;
    vector <EntityVariable *> common;

    if( first->isQuantifier() )
    {
        EntityBaseType ent_bt = first->getType();
        while ( ent_bt == first->getType() )    // ���� ��������� ������� ���������� ������������ �������� ���� ent_bt
        {
            EntityVariable * pev = get<1>( *(first->getParentLink(0)) );    // �������� ��������� ���������� �� ������������ ����� ��� �������
            vev1.push_back(pev);    // ��������� � ��������� ��������� ����������
            first = get<0>( *(first->getParentLink(0)) );     // ��������� � ������������ �������
        }
        while ( ent_bt == second->getType() )    // ���� ������������ ������� ���������� ������������ ���� �� ���� ��������
        {
            EntityVariable * pev = get<1>( *(second->getParentLink(0)) );    // �������� ��������� ���������� �� ������������ ����� ��� �������
            vev2.push_back(pev);    // ��������� � ��������� ��������� ����������
            second = get<0>( *(second->getParentLink(0)) );    // ��������� � ������������ �������
        }
//		first = firstOf;
//		second = secondOf;
        // ��������� ���������� ��������� ���������� �� ����� �������� � ����� ����� ����� ���������� ��� ������� ��������� ������ ���� � ����� ��������
        for(auto curr = vev1.begin(); curr != vev1.end(); curr++)
        {
            for(auto curr2 = vev2.begin(); curr2 != vev2.end(); curr2++ )
            {
                EntityVariable * pev = *curr;
                EntityVariable * pev1 = *curr2;
                if( *pev == *pev1 )
                {
                    common.push_back(pev);
                    break;
                }
            }
        }
        // ������ ����� ���������� ������� ��������� ������ ���� ��� ����� ������ �� ������� ������, �� ����, ���������� ���������� �� ��� ����� ������,
        // � ���������� ���� ����������
        for(auto curr = vev1.begin(); curr != vev1.end(); ++curr)
        {
            bool found = false;
            for(auto curr2 = common.begin(); curr2 != common.end(); curr2++ )
            {
                EntityVariable * pev = *curr;
                EntityVariable * pev1 = *curr2;
                if( *pev == *pev1 )
                {
                    found = true;
                    break;
                }
            }
            if(!found)
            {
                Formula * variant = first->quantifierFormula(ent_bt, *curr);
                if(variant)
                    first = variant;
            }
        }
        // ����� �� �� ��� ������ �������
        for(auto curr = vev2.begin(); curr != vev2.end(); ++curr)
        {
            bool found = false;
            for(auto curr2 = common.begin(); curr2 != common.end(); curr2++ )
            {
                EntityVariable * pev = *curr;
                EntityVariable * pev1 = *curr2;
                if( *pev == *pev1 )
                {
                    found = true;
                    break;
                }
            }
            if(!found)
            {
                Formula * variant = first->quantifierFormula(ent_bt, *curr);
                if(variant)
                    second = variant;
            }
        }
        if( *first == *second )    // ���� ������� �����
            formula = first;    // ��������� ������ �� ���, ��� ����� ��������� �����
    }
    return formula;
}


//
//  ������� ��������� �������������� ������������ ������ �������� �� ��������� ���������� �� ������, ��� ��� �������� ����������� ���������� ��
//  �������� ��������� ������ ��� ����� �� ������. � ������ �������������� ����� ������ ���������� ��������� �� ������� � ����� ������� �����,
//  ����� nullptr
//  K ( x ) ( A ( x ) & B ) =  ( K ( x ) A ( x ) ) & B
//  K ( x ) ( A ( x ) V B ) =  ( K ( x ) A ( x ) ) V B
//
Formula *  IsMovingQuantifierThroughBrackets(const Formula & firstOf, const Formula & secondOf)
{
    Formula * formula = nullptr;
    Formula * first = const_cast<Formula *>(&firstOf);
    Formula * second = const_cast<Formula *>(&secondOf);
    for(int i = 0; i < 2; i++)   // ���� �� ��� �������, ��� ��������� ������������ ������
    {
        if( i == 1 )    // �� ������ ���� �������� ����� ���������� �������, ����� ������ ��������� ������������
        {
            first = const_cast<Formula *>(&secondOf);
            second = const_cast<Formula *>(&firstOf);
        }
        if( first->isQuantifier() && second->isUnion() )
            // ���� ������ ������� ���������� ������������ ��������, � ������ ��������� �����������
        {
            // ������� ������������ �������
            Formula * first_1 = get<0>(* first->getParentLink(0) );    // ������������ ������� ��� ���������� ������������ ��������
            Formula * second_1 = get<0>(* second->getParentLink(0) );    // ������ ������������ ��� ���������� ��� �����������
            Formula * second_2 = get<0>(* second->getParentLink(1) );     // ������ ������������ ��� ���������� ��� �����������
            EntityBaseType ent_bt_first = first->getType();     // ��� ��������, ������������ �������� �������� ������ �������
            EntityBaseType ent_bt_second = second->getType();    // ��� �����������, � ������� �������� �������� ������ �������
            EntityBaseType ent_bt_first_1 = first_1->getType();     // ��� ������������ ������� ��� ���������� ������������ ��������
            EntityBaseType ent_bt_second_1 = second_1->getType();    // ��� ������ ������������ ������� ��� ���������� ��� �����������
            EntityBaseType ent_bt_second_2 = second_2->getType();    // ��� ������ ������������ ������� ��� ���������� ��� �����������
            if( ent_bt_first_1 == ent_bt_second) // ���� ��� ������ ������� (��� �����������) ��������� � ����� �������� ������ �������
            {
                EntityVariable * pev = get<1>(* first->getParentLink(0) );    // ��������� �� ��������� ����������, �� ������� ��� ������� ������� � ������ �������
                // ����������, ������� ����� ������������ �����
                vector <EntityVariable *> * pvev;
                EntityVariable * pev2;
                Formula * second_grandfather;
                Formula * second_parent;
                if( ent_bt_first == ent_bt_second_1 )  // ���� ��� ������ ������� ��������� � ����� ��������� ������� �������� ������
                {
                    pev2 = get<1>(* second_1->getParentLink(0) );  // ��������� �� ��������� ����������, �� ������� ������� ������� ������� �������� ������ �-��
                    pvev = second_2->getFreeVariables();    // ��������� �� ������ ��������� ���������� ������� �������� ������ �������
                    second_grandfather = get<0>(* second_1->getParentLink(0) );   // ��������� �� "����" ������� �������� ������ �������
                    second_parent = second_2;   // ��������� �� ������� �������� ������ �������
                }
                else if(ent_bt_first == ent_bt_second_2 ) // ���� ��� ������ ������� ��������� � ����� ��������� ������� �������� ������
                {
                    pev2 = get<1>(* second_2->getParentLink(0) );  // ��������� �� ��������� ����������, �� ������� ������� ������� ������� �������� ������ �-��
                    pvev = second_1->getFreeVariables();    // ��������� �� ������ ��������� ���������� ������� �������� ������ �������
                    second_grandfather = get<0>(* second_2->getParentLink(0) );   // ��������� �� "����" ������� �������� ������ �������
                    second_parent = second_1;   // ��������� �� ������� �������� ������ �������
                }
                if( *pev == *pev2 )    // ���� ��������� ���������� ��� ��������� � ����� � ������ ������ ���������
                {
                    bool found = false;
                    for(auto it = pvev->begin(); it != pvev->end(); it++ )    // ���� �� ���������� �� ��������� ���������� � �� ������� ��� B � ������
                    // ����� ������� (������� �� ���������� ������������ ��������)
                    {
                        if( **it == *pev )    // ���� ��������� ���������� ���������
                        {
                            found = true;   // ������� ����
                            break;   // ������� �� �����
                        }
                    }
                    if(!found)   // ���� ��������� ���������� �� ������� (������� B �� �������� ����� ��������� ����������)
                    {
                        // ������� "�����" (������������ ������� ��� �������� ����� ����� )
                        Formula * first_1_1 = get<0>( * (first_1->getParentLink(0) ) );
                        Formula * first_1_2 = get<0>( * (first_1->getParentLink(1) ) );
                        // ��������� ��� �������� � �������������
                        if( ( ( *second_grandfather == *first_1_1 ) && ( *second_parent == *first_1_2) ) ||
                            ( ( *second_grandfather == *first_1_2 ) && ( *second_parent == *first_1_1) ) )
                                formula = const_cast<Formula *>(&secondOf);    // ���� ���� ������� ��������, ������ ��������������
                    }
                    else
                    {

                    }
                }
/*
                    // ������� "�����" (������������ ������� ��� ��������� )
                    Formula * first_1_1 = get<0>( * (first_1->getParentLink(0) ) );
                    Formula * second_1_1 = get<0>( *( second_1->getParentLink(0) ) );
                    // ���������, ���������� �� ������� ������������ �������� �� ����� � ��� �� ����������
                    EntityVariable * pev1 = get<1>(* second->getParentLink(0) );
                    EntityVariable * pev2 = get<1>(* first_1->getParentLink(0) );
                    if( ( *pev1 == *pev2 ) && ( *first_1_1 == *second_1_1 ) )    // ���� ���������� ����� (���� � �� ��) � "���������" ������� �����������
                    {
                        formula = first;    // ��������� �������, ������������ � �������� ��� ����� ��������
                    }
                }
*/
            }
            // ���� �������� ������� ��������� ����������� ��������
        }
        if(formula)
            break;
    }
    return formula;
}



//
//  ������� ���������� ��� ������� �� ������� ��������������
//
bool Identity(const Formula& first, const Formula& second)
{
    bool result = false;
    Formula * pfirst = const_cast<Formula *>(&first);
    Formula * psecond = const_cast<Formula *>(&second);
    EntityBaseType first_type = const_cast<Formula *>(&first)->getType();    // ��� ������ ������� (��������� ��� ����������� ����� �������� ����������
    EntityBaseType second_type = ((EntityBase *) &second)->getType();    // ��� ������ ������� (��������� ��� ����������� ����� �������� ����������
    size_t parent_size_1 = pfirst->getNumberOfParents();     // ���������� ������������ ������ (���������) ������ �������
    size_t parent_size_2 = psecond->getNumberOfParents();     // ���������� ������������ ������ (���������) ������ �������

    // ���� �������� ��������������� � � ���
    if( const_cast<Formula *>(&first) == const_cast<Formula *>(&second) )    // ��� - ��������� �� ���� � �� �� �������
        result = true;    // �����������
    else if ( ( first_type == ATOMIC_FORMULA ) && (second_type == ATOMIC_FORMULA ) )    // ���� ��� ������� ���������
//	else if ( first_type == second_type )    // ���� ��� ������� ���� � �� ��
    {
        vector <EntityVariable *> * pfv1 = ((EntityBase *) &first)->getFreeVariables();    // ��������� �� ��������� ��������� ���������� ������ �������
        vector <EntityVariable *> * pfv2 = ((EntityBase *) &second)->getFreeVariables();    // ��������� �� ��������� ��������� ���������� ������ �������
        size_t size_fv_1 = pfv1->size();    // ����� ��������� ���������� ������ �������
        size_t size_fv_2 = pfv2->size();    // ����� ��������� ���������� ������ �������
        if( size_fv_1 == size_fv_2)    // ���������� �������� ��� ��������� ������, ����� ��������� ���������� � ��� ������ ����� 2
        {
            bool found = false;     // ���� ���������� �� ���������� � ����� ��������
            for( size_t i = 0; i < size_fv_1; i++ )    // ������� �� ���� ��������� ���������� ������ �������
            {
                found = false;
                EntityVariable * pev = pfv1->at(i);    // ��������� �� ��������� ���������� ������ �������
                for( size_t i1 = 0; i1 < size_fv_2; i1++ )    // ������� �� ���� ��������� ���������� ������ �������
                {
                    if( *pev == *pfv2->at(i1) )     // ���� ���������� ���������
                    {
                        found = true;
                        break;     // ��������� � ��������� ���������� ������ �������
                    }
                }
                if( !found )     // ���� �����-�� ���������� ������ ������� �� ������� �� ������
                    break;    // ��������� ����
            }
            if( found )    // ���� ��������� � true, ���� ��� ���������� ������ ������� ���������� �� ������
                result = true;    // ������� �����������
        }
    }
    else if ( ( first_type == TUPLE ) && (second_type == TUPLE ) )    // ���� ��� �������
    {
        vector <EntityVariable *> * pfv1 = ((EntityBase *) &first)->getFreeVariables();    // ��������� �� ��������� ��������� ���������� ������ �������
        vector <EntityVariable *> * pfv2 = ((EntityBase *) &second)->getFreeVariables();    // ��������� �� ��������� ��������� ���������� ������ �������
        size_t size_fv_1 = pfv1->size();    // ����� ��������� ���������� ������ �������
        size_t size_fv_2 = pfv2->size();    // ����� ��������� ���������� ������ �������
        if( size_fv_1 == size_fv_2)    // ���������� �������� ��� ��������� ������, ����� ��������� ���������� � ��� ������ ����� 2
        {
            result = true;     // ������ ����� ��������� � true, ��� ������ �� �������������� ��������� ���������� �������� � false � ��������� �������
            for( size_t i = 0; i < size_fv_1; i++ )    // ������� �� ���� ��������� ���������� ������ �������
            {
                EntityVariable * pev = pfv1->at(i);    // ��������� �� ��������� ���������� ������ �������
                if( *pev == *pfv2->at(i) )     // ���� ���������� ���������
                {
                }
                else
                {
                    result = false;
                    break;     // ��������� � ��������� ���������� ������ �������
                }
            }
        }
    }
    else if( (first_type == AND_OPERATION) && (second_type == AND_OPERATION) )   // �������� �� ��������������� "�" � ��������������� "�"
    {
        if( ( parent_size_1 == 2) || (parent_size_2 == 2 ) )// �������� �� ��, ��� � ��������� "�" ����������� �� ��� �������-��������
        {
            Formula * first_1 = get<0>(* pfirst->getParentLink(0) );
            Formula * first_2 = get<0>(* pfirst->getParentLink(1) ) ;
            Formula * second_1 = get<0>(* psecond->getParentLink(0) );
            Formula * second_2 = get<0>(* psecond->getParentLink(1) );
            // �������� �� �� ��������������� "�"
            if( ( (*first_1 == *second_1) && (*first_2 == *second_2) ) || ( (*first_1 == *second_2) && (*first_2 == *second_1) ) )
                result = true;    // ������� �����������
            else   // �������� �� ��������������� "�"  A & (B & C) = (A & B) & C
            {
                if ( IsAssocciativeIdentity(AND_OPERATION, *first_1, *first_2, *second_1, *second_2) )
                    result = true;
            }

        }
        else if ( (first_type == AND_OPERATION) && ( parent_size_1 == 2) )    // �������� �� ��������������� "�" (��������� ����� ��������� ������ �������
        // �� ������)
        {
            Formula * first_1 = get<0>(* pfirst->getParentLink(0) );
            Formula * first_2 = get<0>(* pfirst->getParentLink(1) ) ;
            if( (*first_1 == second) && (*first_2 == second) )    // ���� ��� �������� ������ ������� ��������� �� ������
                result = true;    // ������� �����������
        }
        else if ( (second_type == AND_OPERATION) && ( parent_size_2 == 2) )    // �������� �� ��������������� "�" (��������� ����� ��������� ������ ������� �
        // ������)
        {
            Formula * second_1 = get<0>(* psecond->getParentLink(0) );
            Formula * second_2 = get<0>(* psecond->getParentLink(1) );
            if( (first == *second_1) && (first == *second_2) )    // ���� ��� �������� ������ ������� ��������� � ������
                result = true;    // ������� �����������
        }
    }
    else if( ( (first_type == AND_OPERATION ) || (second_type == OR_OPERATION ) ) ||  ( (first_type == OR_OPERATION ) || (second_type == AND_OPERATION ) ) )
    // �������� �� ������ �������
    {
        if( IsFirstMorganLawIdentity(first, second) )     // �������� �� ������� ������ ������� ( A & B ) = not A V not B
            result = true;
        else if( IsSecondMorganLawIdentity(first, second) )     // �������� �� ������� ������ �������  ( A V B ) = not A & not B
            result = true;
    }
    else if( ( ( (first_type == AND_OPERATION ) || (first_type == OR_OPERATION ) ) && ( ( second_type == QUANTIFIER1_OPERATION ) || ( second_type == QUANTIFIER2_OPERATION ) ) )  ||
        ( ( (second_type == AND_OPERATION ) || (second_type == OR_OPERATION ) ) && ( ( first_type == QUANTIFIER1_OPERATION ) || ( first_type == QUANTIFIER2_OPERATION ) ) ) )
    {
        if( IsMovingQuantifierThroughBrackets(first, second) )
            result = true;
    }
    else if( (first_type == AND_OPERATION ) || (second_type == AND_OPERATION ) )
    {
        if ( IsSecondSplitFormulaIdentity(first, second) )     //  �������� �� ������ ������� ����������� A = ( A V B ) & ( A V not B )
            result = true;
        else if(IsFirstAbsorbtionLawIdentity(first, second))     // �������� �� ������ ����� ���������� A & ( A V B ) = A
            result = true;
    }
    else if( (first_type == OR_OPERATION) && (second_type == OR_OPERATION) )   // �������� �� ��������������� "���" � �� ���������������
    //  "���"  A V (B V C) = (A V B) V C
    {
//		size_t parent_size_1 = first->getNumberOfParents();
//		size_t parent_size_2 = second->getNumberOfParents();
        if( ( parent_size_1 == 2) || (parent_size_2 == 2 ) )// �������� �� ��, ��� � ��������� "���" ����������� �� ��� �������-��������
        {
            Formula * first_1 = get<0>(* pfirst->getParentLink(0) );
            Formula * first_2 = get<0>(* pfirst->getParentLink(1) ) ;
            Formula * second_1 = get<0>(* psecond->getParentLink(0) );
            Formula * second_2 = get<0>(* psecond->getParentLink(1) );
            // �������� �� ������ ��������������
            if( ( (*first_1 == *second_1) && (*first_2 == *second_2) ) && ( (*first_1 == *second_2) && (*first_2 == *second_1) ) )
                result = true;    // ������� �����������
            else   // �������� �� ��������������� "���"  A V (B V C) = (A V B) V C
            {
                if ( IsAssocciativeIdentity(OR_OPERATION, *first_1, *first_2, *second_1, *second_2) )
                    result = true;
            }
        }
        else if ( (first_type == AND_OPERATION) && ( parent_size_1 == 2) )    // �������� �� ��������������� "���" (��������� ����� ��������� ������ �������
        // �� ������)
        {
            Formula * first_1 = get<0>(* pfirst->getParentLink(0) );
            Formula * first_2 = get<0>(* pfirst->getParentLink(1) ) ;
            if( (*first_1 == second) && (*first_2 == second) )    // ���� ��� �������� ������ ������� ��������� �� ������
                result = true;    // ������� �����������
        }
        else if ( (second_type == AND_OPERATION) && ( parent_size_2 == 2) )    // �������� �� ��������������� "���" (��������� ����� ��������� ������ ������� �
        // ������)
        {
            Formula * second_1 = get<0>(* psecond->getParentLink(0) );
            Formula * second_2 = get<0>(* psecond->getParentLink(1) );
            if( (first == *second_1) && (first == *second_2) )    // ���� ��� �������� ������ ������� ��������� � ������
                result = true;    // ������� �����������
        }
    }
    else if( (first_type == OR_OPERATION ) || (second_type == OR_OPERATION ) )
    {
        if(IsSecondAbsorbtionLawIdentity(first, second))      // �������� �� ������ ����� ���������� A V ( A & B ) = A
            result = true;
        else if ( IsFirstSplitFormulaIdentity(first, second) )     //  �������� �� ������ ������� ����������� A = ( A & B ) V ( A & not B )
            result = true;
    }
    else if( (first_type == NEGATIVE_OPERATION ) || (second_type == NEGATIVE_OPERATION ) )
    {
        if( IsDoubleNeativeIdentity(first, second) )    // �������� �� ������ �������� ���������
            result = true;
        else if(IsMoveQuantifierThroughNegotiation(first, second ) )
            result = true;
    }
    else if( ( ( first_type == QUANTIFIER1_OPERATION ) &&  ( second_type == QUANTIFIER1_OPERATION ) ) ||
        ( first_type == QUANTIFIER2_OPERATION ) && ( second_type == QUANTIFIER2_OPERATION ) )
    {
        if( IsReplaceSameQuantifiers(first, second) )    // ������������ ����������� ���������
            result = true;
        else if( ( parent_size_1 == 1) && ( parent_size_2 == 1) )
        {
            Formula * first_parent = get<0>(* pfirst->getParentLink(0) );
            Formula * second_parent = get<0>(* psecond->getParentLink(0) );
            EntityVariable * pfv1 =  get<1>(* pfirst->getParentLink(0) );
            EntityVariable * pfv2 =  get<1>(* psecond->getParentLink(0) );
            if( ( *first_parent == *second_parent ) && (*pfv1 == *pfv2) )
                result = true;
        }
    }
    return result;
}



bool operator == (const Formula & first, const Formula & second )
{
    EntityBase * base1 = (EntityBase *) &first;
    EntityBase * base2 = (EntityBase *) &second;
    if(base1->isRedefined() || base2->isRedefined())
    {
        return (base1 == base2);
    }
    return Identity(first, second);
}
