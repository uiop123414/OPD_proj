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
// проверка на равносильность двух пар формул по ассоциативности "И"  A & (B & C) = (A & B) & C
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
		// делаем перебор всех возможных случаев, когда ни одна формулы из любой пары не равносильна любой формуле из другой.

		// смотрим, образованы ли в свою очередь второй родитель первой сравниваемой формулы и первый родитель второй сравниваемой 
		// формулы путем объединения "И" каждый
		if( ( pfirst_2->getType() == ent_bt ) && (  psecond_1->getType() == ent_bt ) )
		{
			// 
			if( ( pfirst_2->getNumberOfParents() == 2 ) && (  psecond_1->getNumberOfParents() == 2 ) )    // избыточная проверка
			{
				// получаем указатели на родителей второго родителя первой сравниваемой формулы и первого родителя второй сравниваемой формлуы
				Formula * first_2_1 = get<0>(* pfirst_2->getParentLink(0) );    
				Formula * first_2_2 = get<0>(* pfirst_2->getParentLink(1) ) ;
				Formula * second_1_1 = get<0>(* psecond_1->getParentLink(0) );
				Formula * second_1_2 = get<0>(* psecond_1->getParentLink(1) );
				// проверяем ассоциативность, рассматриваем все возможные перестановки для этого случая	
				if ( ( ( first_1 == *second_1_1 ) && ( *first_2_1 == *second_1_2 ) && (*first_2_2 == second_2 ) ) || 
					( ( first_1 == *second_1_2 ) && ( *first_2_1 == *second_1_1 ) && (*first_2_2 == second_2 ) ) ||
					( ( first_1 == *second_1_2 ) && ( *first_2_1 == second_2 ) && (*first_2_2 == *second_1_1 ) ) ||
					( ( first_1 == *second_1_1 ) && ( *first_2_1 == second_2 ) && (*first_2_2 == *second_1_2 ) ) )
						return true;
			}
		}
		// или смотрим, образованы ли в свою очередь первый родитель первой сравниваемой формулы и первый родитель второй сравниваемой 
		// формулы путем объединения "И" каждый.
		if( ( pfirst_1->getType() == ent_bt ) && ( psecond_1->getType() == ent_bt ) )
		{
			if( ( pfirst_1->getNumberOfParents() == 2 ) && ( psecond_1->getNumberOfParents() == 2 ) )    // избыточная проверка
			{
				// получаем указатели на родителей второго родителя первой сравниваемой формулы и первого родителя второй сравниваемой формлуы
				Formula * first_1_1 = get<0>(* pfirst_1->getParentLink(0) );    
				Formula * first_1_2 = get<0>(* pfirst_1->getParentLink(1) ) ;
				Formula * second_1_1 = get<0>(* psecond_1->getParentLink(0) );
				Formula * second_1_2 = get<0>(* psecond_1->getParentLink(1) );
				// проверяем ассоциативность, рассматриваем все возможные перестановки для этого случая
				if ( ( ( first_2 == *second_1_1 ) && ( *first_1_1 == *second_1_2 ) && (*first_1_2 == second_2 ) ) || 
					( ( first_2 == *second_1_1 ) && ( *first_1_1 == second_2 ) && (*first_1_2 == *second_1_2 ) ) ||
					( ( first_2 == *second_1_2 ) && ( *first_1_1 == *second_1_1 ) && (*first_1_2 == second_2 ) ) ||
					( ( first_2 == *second_1_2 ) && ( *first_1_1 == second_2 ) && (*first_1_2 == *second_1_1 ) ) )
						return true;
			}
		}
		// или смотрим, образованы ли в свою очередь первый родитель первой сравниваемой формулы и второй родитель второй сравниваемой 
		// формулы путем объединения "И" каждый.
		if( ( pfirst_1->getType() == ent_bt ) && ( psecond_2->getType() == ent_bt ) )
		{
			if( ( pfirst_1->getNumberOfParents() == 2 ) && ( psecond_2->getNumberOfParents() == 2 ) )    // избыточная проверка
			{
				// получаем указатели на родителей второго родителя первой сравниваемой формулы и первого родителя второй сравниваемой формлуы
				Formula * first_1_1 = get<0>(* pfirst_1->getParentLink(0) );    
				Formula * first_1_2 = get<0>(* pfirst_1->getParentLink(1) ) ;
				Formula * second_2_1 = get<0>(* psecond_2->getParentLink(0) );
				Formula * second_2_2 = get<0>(* psecond_2->getParentLink(1) );
				// проверяем ассоциативность, рассматриваем все возможные перестановки для этого случая
				if ( ( ( first_2 == *second_2_1 ) && ( *first_1_1 == *second_2_2 ) && (*first_1_2 == second_1 ) ) || 
					( ( first_2 == *second_2_1 ) && ( *first_1_1 == second_1 ) && (*first_1_2 == *second_2_2 ) ) ||
					( ( first_2 == *second_2_2 ) && ( *first_1_1 == *second_2_1 ) && (*first_1_2 == second_1 ) ) ||
					( ( first_2 == *second_2_2 ) && ( *first_1_1 == second_1 ) && (*first_1_2 == *second_2_1 ) ) )
						return true;
			}
		}
		// или смотрим, образованы ли в свою очередь второй родитель первой сравниваемой формулы и второй родитель второй сравниваемой 
		// формулы путем объединения "И" каждый
		if( ( pfirst_2->getType() == ent_bt ) && ( psecond_2->getType() == ent_bt ) )
		{
			if( ( pfirst_2->getNumberOfParents() == 2 ) && ( psecond_2->getNumberOfParents() == 2 ) )    // избыточная проверка
			{
				// получаем указатели на родителей второго родителя первой сравниваемой формулы и второго родителя второй сравниваемой формлуы
				Formula * first_2_1 = get<0>(* pfirst_2->getParentLink(0) );    
				Formula * first_2_2 = get<0>(* pfirst_2->getParentLink(1) ) ;
				Formula * second_2_1 = get<0>(* psecond_2->getParentLink(0) );
				Formula * second_2_2 = get<0>(* psecond_2->getParentLink(1) );
				// проверяем ассоциативность, рассматриваем все возможные перестановки для этого случая
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
//  функция проверяет равносильность согласно первому закону поглощения, в случае равносильности возвращает указатель на более простую формулу, иначе nullptr
//  A & (A V B) = A
//
Formula * IsFirstAbsorbtionLawIdentity(const Formula& firstOf, const Formula& secondOf)
{
	Formula * formula = nullptr;
	Formula * first = const_cast<Formula *>(&firstOf);
	Formula * second = const_cast<Formula *>(&secondOf);
	for(int i = 0; i < 2; i++)
	{
		if( i == 1 )    // на втором шаге итерации меняю переменные местами, чтобы учесть возможные перестановки
		{
			first = const_cast<Formula *>(&secondOf);
			second = const_cast<Formula *>(&firstOf);
		}
		if( (first->getType() == AND_OPERATION ) && (first->getNumberOfParents() == 2) )   // если первая формула образована объединением "И"
		{
			// получаю родительские формулы для формулы firstOf
			Formula * first_1 = get<0>(* first->getParentLink(0) );  
			Formula * first_2 = get<0>(* first->getParentLink(1) );
			if( *first_1 == *second )    // если первый родитель первой формулы совпадает со второй
			{
				if( ( first_2->getType() == OR_OPERATION ) && ( first_2->getNumberOfParents() == 2 ) )
				{
					if( ( *get<0>( *first_2->getParentLink(0) ) == *second ) ||
						( *get<0>( *first_2->getParentLink(1) ) == *second ) )
							formula = second;
				}
			}
			else if( *first_2 == *second )    // если второй родитель первой формулы совпадает со второй
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
//  функция проверяет равносильность согласно второму закону поглощения, в случае равносильности возвращает указатель на более простую формулу, иначе nullptr
//  A V ( A & B ) = A
//
Formula * IsSecondAbsorbtionLawIdentity(const Formula& firstOf, const Formula& secondOf)
{
	Formula * formula = nullptr;
	Formula * first = const_cast<Formula *>(&firstOf);
	Formula * second = const_cast<Formula *>(&secondOf);
	for(int i = 0; i < 2; i++)
	{
		if( i == 1 )    // на втором шаге итерации меняю переменные местами, чтобы учесть возможные перестановки
		{
			first = const_cast<Formula *>(&secondOf);
			second = const_cast<Formula *>(&firstOf);
		}
		if( (first->getType() == OR_OPERATION ) && (first->getNumberOfParents() == 2) )   // если первая формула образована объединением "ИЛИ"
		{
			// получаю родительские формулы для формулы firstOf
			Formula * first_1 = get<0>(* first->getParentLink(0) );  
			Formula * first_2 = get<0>(* first->getParentLink(1) );
			if( *first_1 == *second )    // если первый родитель первой формулы совпадает со второй
			{
				if( ( first_2->getType() == AND_OPERATION ) && ( first_2->getNumberOfParents() == 2 ) )
				{
					if( ( *get<0>( *first_2->getParentLink(0) ) == *second ) ||
						( *get<0>( *first_2->getParentLink(1) ) == *second ) )
							formula = second;
				}
			}
			else if( *first_2 == *second )    // если второй родитель первой формулы совпадает со второй
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
//  функция проверяет равносильность применительно к снятию двойного отрицания, в случае равносильности обеих формул возвращает указатель на 
// формулу в более простой форме, иначе nullptr
//  not ( not A ) = A
//
Formula * IsDoubleNeativeIdentity(const Formula& firstOf, const Formula& secondOf)
{
	Formula * formula = nullptr;
	Formula * first = const_cast<Formula *>(&firstOf);
	Formula * second = const_cast<Formula *>(&secondOf);
	for(int i = 0; i < 2; i++)
	{
		if( i == 1 )    // на втором шаге итерации меняю переменные местами, чтобы учесть возможные перестановки
		{
			first = const_cast<Formula *>(&secondOf);
			second = const_cast<Formula *>(&firstOf);
		}
		if( (first->getType() == NEGATIVE_OPERATION ) && (first->getNumberOfParents() == 1) )   // если первая формула образована операцией отрицания
		{
			// получаю родительские формулы для формулы firstOf
			Formula * first_1 = get<0>(* first->getParentLink(0) );  

			if( (first_1->getType() == NEGATIVE_OPERATION ) && (first->getNumberOfParents() == 1) )    // если родитель формулы также образован операцией отрицания
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
//  функция проверяет равносильность по первому закону Моргана, в случае равносильности обеих формул возвращает указатель на 
// формулу в более простой форме, иначе nullptr
//  ( A & B ) = not A V not B
//
Formula * IsFirstMorganLawIdentity(const Formula& firstOf, const Formula& secondOf)
{
	Formula * formula = nullptr;
	Formula * first = const_cast<Formula *>(&firstOf);
	Formula * second = const_cast<Formula *>(&secondOf);
	for(int i = 0; i < 2; i++)
	{
		if( i == 1 )    // на втором шаге итерации меняю переменные местами, чтобы учесть возможные перестановки
		{
			first = const_cast<Formula *>(&secondOf);
			second = const_cast<Formula *>(&firstOf);
		}
		if( (first->getType() == AND_OPERATION ) && (first->getNumberOfParents() == 2) )   // если первая формула образована объединением "И"
		{
			// получаю родительские формулы для формулы first
			Formula * first_1 = get<0>(* first->getParentLink(0) );  
			Formula * first_2 = get<0>(* first->getParentLink(1) );  

			if( (first_1->getType() == OR_OPERATION ) && (first->getNumberOfParents() == 2) )    // если вторая формула образована операцией объединением "ИЛИ"
			{
				// получаю родительские формулы для формулы first
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
//  функция проверяет равносильность по второму закону Моргана, в случае равносильности обеих формул возвращает указатель на 
// формулу в более простой форме, иначе nullptr
//  ( A V B ) = not A & not B
//
Formula * IsSecondMorganLawIdentity(const Formula& firstOf, const Formula& secondOf)
{
	Formula * formula = nullptr;
	Formula * first = const_cast<Formula *>(&firstOf);
	Formula * second = const_cast<Formula *>(&secondOf);
	for(int i = 0; i < 2; i++)
	{
		if( i == 1 )    // на втором шаге итерации меняю переменные местами, чтобы учесть возможные перестановки
		{
			first = const_cast<Formula *>(&secondOf);
			second = const_cast<Formula *>(&firstOf);
		}
		if( (first->getType() == OR_OPERATION ) && (first->getNumberOfParents() == 2) )   // если первая формула образована объединением "И"
		{
			// получаю родительские формулы для формулы first
			Formula * first_1 = get<0>(* first->getParentLink(0) );  
			Formula * first_2 = get<0>(* first->getParentLink(1) );  

//			if( (first_1->getType() == AND_OPERATION ) && (first->getNumberOfParents() == 2) )    // если вторая формула образована операцией объединением "ИЛИ"
			if( (second->getType() == AND_OPERATION ) && (second->getNumberOfParents() == 2) )    // если вторая формула образована операцией объединением "ИЛИ"
			{
				// получаю родительские формулы для формулы first
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
//  функция проверяет равносильность применительно к первой формуле расщепления, в случае равносильности обеих формул возвращает указатель на 
// формулу в более простой форме, иначе nullptr
//  A = ( A & B ) V ( A & not B )
//
Formula * IsFirstSplitFormulaIdentity(const Formula& firstOf, const Formula& secondOf)
{
	Formula * formula = nullptr;
	Formula * first = const_cast<Formula *>(&firstOf);
	Formula * second = const_cast<Formula *>(&secondOf);
	for(int i = 0; i < 2; i++)
	{
		if( i == 1 )    // на втором шаге итерации меняю переменные местами, чтобы учесть возможные перестановки
		{
			first = const_cast<Formula *>(&secondOf);
			second = const_cast<Formula *>(&firstOf);
		}
		if( (first->getType() == OR_OPERATION ) && (first->getNumberOfParents() == 2) )   // если первая формула образована объединением "ИЛИ"
		{
			// получаю родительские формулы для формулы first
			Formula * first_1 = get<0>(* first->getParentLink(0) );  
			Formula * first_2 = get<0>(* first->getParentLink(1) );  
			// если оба родителя первой формулы образован объединением "И" каждый
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
//  функция проверяет равносильность применительно ко второй формуле расщепления, в случае равносильности обеих формул возвращает указатель на 
// формулу в более простой форме, иначе nullptr
//  A = ( A V B ) & ( A V not B )
//
Formula * IsSecondSplitFormulaIdentity(const Formula& firstOf, const Formula& secondOf)
{
	Formula * formula = nullptr;
	Formula * first = const_cast<Formula *>(&firstOf);
	Formula * second = const_cast<Formula *>(&secondOf);
	for(int i = 0; i < 2; i++)
	{
		if( i == 1 )    // на втором шаге итерации меняю переменные местами, чтобы учесть возможные перестановки
		{
			first = const_cast<Formula *>(&secondOf);
			second = const_cast<Formula *>(&firstOf);
		}
		if( (first->getType() == AND_OPERATION ) && (first->getNumberOfParents() == 2) )   // если первая формула образована объединением "ИЛИ"
		{
			// получаю родительские формулы для формулы first
			Formula * first_1 = get<0>(* first->getParentLink(0) );  
			Formula * first_2 = get<0>(* first->getParentLink(1) );  
			// если оба родителя первой формулы образован объединением "И" каждый
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
//  функция проверяет равносильность применительно к переносу квантора через операцию отрицания для формулы со свободной переменной, по которой он навешан, 
//  в случае равносильности обеих формул возвращает указатель на формулу в более простой форме, иначе nullptr
//  not ( K x ) A ( x ) = ( K x ) not A ( x )
//
Formula * IsMoveQuantifierThroughNegotiation(const Formula& firstOf, const Formula& secondOf)
{
	Formula * formula = nullptr;
	Formula * first = const_cast<Formula *>(&firstOf);
	Formula * second = const_cast<Formula *>(&secondOf);
	for(int i = 0; i < 2; i++)
	{
		if( i == 1 )    // на втором шаге итерации меняю переменные местами, чтобы учесть возможные перестановки
		{
			first = const_cast<Formula *>(&secondOf);
			second = const_cast<Formula *>(&firstOf);
		}
		if( first->isNegative() && second->isQuantifier() )
			// если первая формула образована операцией отрицания, а вторая навешиванием квантора
		{
			// получаю родительские формулы для обеих
			Formula * first_1 = get<0>(* first->getParentLink(0) );  
			Formula * second_1 = get<0>(* second->getParentLink(0) );  
			EntityBaseType ent_bt = second->getType();
			if( first_1->isQuantifier() && (first->getType() != ent_bt ) && second_1->isNegative() )
			{
				// получаю "дедов" (родительские формулы для родителей )
				Formula * first_1_1 = get<0>( * (first_1->getParentLink(0) ) );  
				Formula * second_1_1 = get<0>( *( second_1->getParentLink(0) ) );  
				// определяю, образованы ли формулы навешиванием квантора по одной и той же переменной
				EntityVariable * pev1 = get<1>(* second->getParentLink(0) );
				EntityVariable * pev2 = get<1>(* first_1->getParentLink(0) );
				if( ( *pev1 == *pev2 ) && ( *first_1_1 == *second_1_1 ) )    // если переменные равны (одна и та же) и "дедовские" формулы равносильны
				{
					formula = first;    // возвращаю формулу, начинающуюся с квантора как более принятую
				}
			}
			// если родитель формулы образован навешивание квантора
		}
		if(formula)
			break;
	}
	return formula;
}

//
//  функция переставляет два последних одноимённых квантора в формула и возвращает указатель на сознданную формулу, nullptr если неудача
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
//  функция проверяет равносильность относительно перестановки одноименных кванторов, 
//  в случае равносильности обеих формул возвращает указатель на формулу в более простой форме, иначе nullptr
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
		while ( ent_bt == first->getType() )    // если очередная формула образована навешиванием квантора типа ent_bt
		{
			EntityVariable * pev = get<1>( *(first->getParentLink(0)) );    // получаем свободную переменную из родительской связи для формулы
			vev1.push_back(pev);    // добавляем в контейнер свободных переменных 
			first = get<0>( *(first->getParentLink(0)) );     // переходим к родительской формуле
		}
		while ( ent_bt == second->getType() )    // если сравниваемая формула образована навешиванием того же типа квантора
		{
			EntityVariable * pev = get<1>( *(second->getParentLink(0)) );    // получаем свободную переменную из родительской связи для формулы
			vev2.push_back(pev);    // добавляем в контейнер свободных переменных 
			second = get<0>( *(second->getParentLink(0)) );    // переходим к родительской формуле
		}
//		first = firstOf;
//		second = secondOf;		
		// сравниваю контейнеры свободных переменных по обеим формулам с целью найти общие переменные для цепочки кванторов одного вида в обеих формулах
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
		// вывожу общие переменные цепочки кванторов одного вида для обоих формул за пределы формул, то есть, фактически отбрасываю их для обоих формул,
		// а оставшееся буду сравнивать 
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
		// делаю то же для второй формулы
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
		if( *first == *second )    // если формулы равны
			formula = first;    // возвращаю первую из них, вот здесь случайный выбор
	}
	return formula;
}


//
//  функция проверяет равносильность относительно выноса квантора по свободной переменной за скобки, где при операции объединения переменная не 
//  является свободной только для одной из формул. в случае равносильности обеих формул возвращает указатель на формулу в более простой форме, 
//  иначе nullptr
//  K ( x ) ( A ( x ) & B ) =  ( K ( x ) A ( x ) ) & B 
//  K ( x ) ( A ( x ) V B ) =  ( K ( x ) A ( x ) ) V B 
//
Formula *  IsMovingQuantifierThroughBrackets(const Formula & firstOf, const Formula & secondOf)
{
	Formula * formula = nullptr;
	Formula * first = const_cast<Formula *>(&firstOf);
	Formula * second = const_cast<Formula *>(&secondOf);
	for(int i = 0; i < 2; i++)   // цикл на два прохода, для возможной перестановки формул
	{
		if( i == 1 )    // на втором шаге итерации меняю переменные местами, чтобы учесть возможные перестановки
		{
			first = const_cast<Formula *>(&secondOf);
			second = const_cast<Formula *>(&firstOf);
		}
		if( first->isQuantifier() && second->isUnion() )
			// если первая формула образована навешиванием квантора, а вторая операцией объединения
		{
			// получаю родительские формулы 
			Formula * first_1 = get<0>(* first->getParentLink(0) );    // родительская формула для полученной навешиванием кванторо
			Formula * second_1 = get<0>(* second->getParentLink(0) );    // первая родительская для полученной при объединении
			Formula * second_2 = get<0>(* second->getParentLink(1) );     // вторая родительская для полученной при объединении
			EntityBaseType ent_bt_first = first->getType();     // тип квантора, навешиванием которого получена первая формула
			EntityBaseType ent_bt_second = second->getType();    // тип объединения, с помощью которого получена вторая формула
			EntityBaseType ent_bt_first_1 = first_1->getType();     // тип родительской формулы для полученной навешиванием квантора
			EntityBaseType ent_bt_second_1 = second_1->getType();    // тип первой родительской формулы для полученной при объединении 
			EntityBaseType ent_bt_second_2 = second_2->getType();    // тип второй родительской формулы для полученной при объединении 
			if( ent_bt_first_1 == ent_bt_second) // если тип второй формулы (тип объединения) совпадает с типом родителя первой формулы
			{
				EntityVariable * pev = get<1>(* first->getParentLink(0) );    // указатель на свободную переменную, по которой был навешан квантор в первой формуле
				// переменные, которые будут использованы далее
				vector <EntityVariable *> * pvev;
				EntityVariable * pev2;
				Formula * second_grandfather;
				Formula * second_parent;
				if( ent_bt_first == ent_bt_second_1 )  // если тип первой формулы совпадает с видом квантором первого родителя второй
				{
					pev2 = get<1>(* second_1->getParentLink(0) );  // указатель на свободную переменную, по которой навешан квантор первого родителя второй ф-лы
					pvev = second_2->getFreeVariables();    // указатель на вектор свободных переменных второго родителя второй формулы
					second_grandfather = get<0>(* second_1->getParentLink(0) );   // указатель на "деда" первого родителя второй формулы
					second_parent = second_2;   // указатель на второго родителя второй формулы
				}
				else if(ent_bt_first == ent_bt_second_2 ) // если тип первой формулы совпадает с видом квантором второго родителя второй 
				{
					pev2 = get<1>(* second_2->getParentLink(0) );  // указатель на свободную переменную, по которой навешан квантор второго родителя второй ф-лы
					pvev = second_1->getFreeVariables();    // указатель на вектор свободных переменных первого родителя второй формулы
					second_grandfather = get<0>(* second_2->getParentLink(0) );   // указатель на "деда" второго родителя второй формулы
					second_parent = second_1;   // указатель на первого родителя второй формулы
				}
				if( *pev == *pev2 )    // если свободные переменные для кванторов с левой и правой сторон совпадают
				{
					bool found = false; 
					for(auto it = pvev->begin(); it != pvev->end(); it++ )    // цикл по указателям на свободные переменные в их векторе для B в правой 
					// части формулы (которая не образована навешиванием квантора)
					{
						if( **it == *pev )    // если свободные переменные совпадают
						{
							found = true;   // взводим флаг
							break;   // выходим из цикла
						}
					}
					if(!found)   // если свободная переменная не найдена (формула B не содержит такую свободную переменную)
					{
						// получаю "дедов" (родительские формулы для родителя левой части )
						Formula * first_1_1 = get<0>( * (first_1->getParentLink(0) ) );  
						Formula * first_1_2 = get<0>( * (first_1->getParentLink(1) ) );  
						// сравниваю два варианта с перестановкой
						if( ( ( *second_grandfather == *first_1_1 ) && ( *second_parent == *first_1_2) ) ||
							( ( *second_grandfather == *first_1_2 ) && ( *second_parent == *first_1_1) ) )
								formula = const_cast<Formula *>(&secondOf);    // если один вариант сопадает, значит равносильность
					}
					else
					{

					}
				}
/*
					// получаю "дедов" (родительские формулы для родителей )
					Formula * first_1_1 = get<0>( * (first_1->getParentLink(0) ) );  
					Formula * second_1_1 = get<0>( *( second_1->getParentLink(0) ) );  
					// определяю, образованы ли формулы навешиванием квантора по одной и той же переменной
					EntityVariable * pev1 = get<1>(* second->getParentLink(0) );
					EntityVariable * pev2 = get<1>(* first_1->getParentLink(0) );
					if( ( *pev1 == *pev2 ) && ( *first_1_1 == *second_1_1 ) )    // если переменные равны (одна и та же) и "дедовские" формулы равносильны
					{
						formula = first;    // возвращаю формулу, начинающуюся с квантора как более принятую
					}
				}
*/
			}
			// если родитель формулы образован навешивание квантора
		}
		if(formula)
			break;
	}
	return formula;
}



//
//  функция сравнивает две формулы на предмет равносильности
//
bool Identity(const Formula& first, const Formula& second)
{
	bool result = false;
	Formula * pfirst = const_cast<Formula *>(&first);
	Formula * psecond = const_cast<Formula *>(&second);
	EntityBaseType first_type = const_cast<Formula *>(&first)->getType();    // тип первой формулы (атомарная или применением какой операции образована
	EntityBaseType second_type = ((EntityBase *) &second)->getType();    // тип второй формулы (атомарная или применением какой операции образована
	size_t parent_size_1 = pfirst->getNumberOfParents();     // количество родительских связей (родителей) первой формулы
	size_t parent_size_2 = psecond->getNumberOfParents();     // количество родительских связей (родителей) второй формулы

	// надо добавить ассоциативность И и ИЛИ
	if( const_cast<Formula *>(&first) == const_cast<Formula *>(&second) )    // оба - указатели на одну и ту же формулу
		result = true;    // равносильны
	else if ( ( first_type == ATOMIC_FORMULA ) && (second_type == ATOMIC_FORMULA ) )    // если обе формулы атомарные
//	else if ( first_type == second_type )    // если обе формулы одна и та же
	{
		vector <EntityVariable *> * pfv1 = ((EntityBase *) &first)->getFreeVariables();    // указатель на контейнер свободных переменных первой формулы
		vector <EntityVariable *> * pfv2 = ((EntityBase *) &second)->getFreeVariables();    // указатель на контейнер свободных переменных второй формулы
		size_t size_fv_1 = pfv1->size();    // число свободных переменных первой формулы
		size_t size_fv_2 = pfv2->size();    // число свободных переменных второй формулы
		if( size_fv_1 == size_fv_2)    // избыточная проверка для атомарных формул, число свободных переменных у них всегда равно 2
		{
			bool found = false;     // флаг существует ли переменная в обеих формулах
			for( size_t i = 0; i < size_fv_1; i++ )    // перебор по всем свободным переменным первой формулы
			{
				found = false;
				EntityVariable * pev = pfv1->at(i);    // указатель на свободную переменную первой формулы
				for( size_t i1 = 0; i1 < size_fv_2; i1++ )    // перебор по всем свободным перепенным второй формулы
				{
					if( *pev == *pfv2->at(i1) )     // если переменные совпадают
					{
						found = true;
						break;     // переходим к следующей переменной первой формулы
					}
				}
				if( !found )     // если какая-то переменная первой формулы не найдена во второй
					break;    // прерываем цикл
			}
			if( found )    // флаг выставлен в true, если все переменные первой формулы содержатся во второй
				result = true;    // формулы равносильны
		}
	}
	else if ( ( first_type == TUPLE ) && (second_type == TUPLE ) )    // если оба кортежа
	{
		vector <EntityVariable *> * pfv1 = ((EntityBase *) &first)->getFreeVariables();    // указатель на контейнер свободных переменных первой формулы
		vector <EntityVariable *> * pfv2 = ((EntityBase *) &second)->getFreeVariables();    // указатель на контейнер свободных переменных второй формулы
		size_t size_fv_1 = pfv1->size();    // число свободных переменных первой формулы
		size_t size_fv_2 = pfv2->size();    // число свободных переменных второй формулы
		if( size_fv_1 == size_fv_2)    // избыточная проверка для атомарных формул, число свободных переменных у них всегда равно 2
		{
			result = true;     // ставим сразу результат в true, при первом же несоответствии свободных переменных выставим в false и прерываем перебор
			for( size_t i = 0; i < size_fv_1; i++ )    // перебор по всем свободным переменным первой формулы
			{
				EntityVariable * pev = pfv1->at(i);    // указатель на свободную переменную первой формулы
				if( *pev == *pfv2->at(i) )     // если переменные совпадают
				{
				}
				else
				{
					result = false;
					break;     // переходим к следующей переменной первой формулы
				}
			}
		}
	}
	else if( (first_type == AND_OPERATION) && (second_type == AND_OPERATION) )   // проверка на коммутативность "И" и ассоциативность "И"
	{
		if( ( parent_size_1 == 2) || (parent_size_2 == 2 ) )// проверка на то, что в операциях "И" участвовали по две формулы-родителя
		{
			Formula * first_1 = get<0>(* pfirst->getParentLink(0) );
			Formula * first_2 = get<0>(* pfirst->getParentLink(1) ) ;
			Formula * second_1 = get<0>(* psecond->getParentLink(0) );
			Formula * second_2 = get<0>(* psecond->getParentLink(1) );
			// проверка на на коммутативность "И"
			if( ( (*first_1 == *second_1) && (*first_2 == *second_2) ) || ( (*first_1 == *second_2) && (*first_2 == *second_1) ) )
				result = true;    // формулы равносильны
			else   // проверка на ассоциативность "И"  A & (B & C) = (A & B) & C
			{
				if ( IsAssocciativeIdentity(AND_OPERATION, *first_1, *first_2, *second_1, *second_2) )
					result = true;
			}

		}
		else if ( (first_type == AND_OPERATION) && ( parent_size_1 == 2) )    // проверка на идемпотентность "И" (сравниваю обоих родителей первой формулы 
		// со второй)
		{
			Formula * first_1 = get<0>(* pfirst->getParentLink(0) );
			Formula * first_2 = get<0>(* pfirst->getParentLink(1) ) ;
			if( (*first_1 == second) && (*first_2 == second) )    // если оба родителя первой формулы совпадают со второй
				result = true;    // формулы равносильны
		}
		else if ( (second_type == AND_OPERATION) && ( parent_size_2 == 2) )    // проверка на идемпотентность "И" (сравниваю обоих родителей второй формулы с
		// первой)
		{
			Formula * second_1 = get<0>(* psecond->getParentLink(0) );
			Formula * second_2 = get<0>(* psecond->getParentLink(1) );
			if( (first == *second_1) && (first == *second_2) )    // если оба родителя второй формулы совпадают с первой
				result = true;    // формулы равносильны
		}
	}
	else if( ( (first_type == AND_OPERATION ) || (second_type == OR_OPERATION ) ) ||  ( (first_type == OR_OPERATION ) || (second_type == AND_OPERATION ) ) )
	// проверка на законы Моргана
	{
		if( IsFirstMorganLawIdentity(first, second) )     // проверка по первому закону Моргана ( A & B ) = not A V not B
			result = true;
		else if( IsSecondMorganLawIdentity(first, second) )     // проверка по второму закону Моргана  ( A V B ) = not A & not B
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
		if ( IsSecondSplitFormulaIdentity(first, second) )     //  проверка на вторую формулу расщепления A = ( A V B ) & ( A V not B )
			result = true;
		else if(IsFirstAbsorbtionLawIdentity(first, second))     // проверка на первый закон поглощения A & ( A V B ) = A
			result = true;
	}
	else if( (first_type == OR_OPERATION) && (second_type == OR_OPERATION) )   // проверка на коммутативность "ИЛИ" и на ассоциативность 
	//  "ИЛИ"  A V (B V C) = (A V B) V C
	{
//		size_t parent_size_1 = first->getNumberOfParents();
//		size_t parent_size_2 = second->getNumberOfParents();
		if( ( parent_size_1 == 2) || (parent_size_2 == 2 ) )// проверка на то, что в операциях "ИЛИ" участвовали по две формулы-родителя
		{
			Formula * first_1 = get<0>(* pfirst->getParentLink(0) );
			Formula * first_2 = get<0>(* pfirst->getParentLink(1) ) ;
			Formula * second_1 = get<0>(* psecond->getParentLink(0) );
			Formula * second_2 = get<0>(* psecond->getParentLink(1) );
			// проверка на первую равносильность
			if( ( (*first_1 == *second_1) && (*first_2 == *second_2) ) && ( (*first_1 == *second_2) && (*first_2 == *second_1) ) )
				result = true;    // формулы равносильны
			else   // проверка на ассоциативность "ИЛИ"  A V (B V C) = (A V B) V C
			{
				if ( IsAssocciativeIdentity(OR_OPERATION, *first_1, *first_2, *second_1, *second_2) )
					result = true;
			}
		}
		else if ( (first_type == AND_OPERATION) && ( parent_size_1 == 2) )    // проверка на идемпотентность "ИЛИ" (сравниваю обоих родителей первой формулы 
		// со второй)
		{
			Formula * first_1 = get<0>(* pfirst->getParentLink(0) );
			Formula * first_2 = get<0>(* pfirst->getParentLink(1) ) ;
			if( (*first_1 == second) && (*first_2 == second) )    // если оба родителя первой формулы совпадают со второй
				result = true;    // формулы равносильны
		}
		else if ( (second_type == AND_OPERATION) && ( parent_size_2 == 2) )    // проверка на идемпотентность "ИЛИ" (сравниваю обоих родителей второй формулы с
		// первой)
		{
			Formula * second_1 = get<0>(* psecond->getParentLink(0) );
			Formula * second_2 = get<0>(* psecond->getParentLink(1) );
			if( (first == *second_1) && (first == *second_2) )    // если оба родителя второй формулы совпадают с первой
				result = true;    // формулы равносильны
		}
	}
	else if( (first_type == OR_OPERATION ) || (second_type == OR_OPERATION ) )
	{
		if(IsSecondAbsorbtionLawIdentity(first, second))      // проверка на второй закон поглощения A V ( A & B ) = A
			result = true;
		else if ( IsFirstSplitFormulaIdentity(first, second) )     //  проверка на первую формулу расщепления A = ( A & B ) V ( A & not B )
			result = true;
	}
	else if( (first_type == NEGATIVE_OPERATION ) || (second_type == NEGATIVE_OPERATION ) )
	{
		if( IsDoubleNeativeIdentity(first, second) )    // проверка на снятие двойного отрицания
			result = true;
		else if(IsMoveQuantifierThroughNegotiation(first, second ) )
			result = true;
	}
	else if( ( ( first_type == QUANTIFIER1_OPERATION ) &&  ( second_type == QUANTIFIER1_OPERATION ) ) ||
		( first_type == QUANTIFIER2_OPERATION ) && ( second_type == QUANTIFIER2_OPERATION ) )
	{
		if( IsReplaceSameQuantifiers(first, second) )    // перестановка одноименных кванторов
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
