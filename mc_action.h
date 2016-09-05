#ifndef MC_ACTION_INCLUDED
# define MC_ACTION_INCLUDED

#include "mc_parser.tab.hh"

namespace MC
{

class MC_Action
{
private:
	double m_pushNumber;
	MC::MC_Parser::token::yytokentype m_act;
	std::stack<double>& m_stack;

public:
	MC_Action(std::stack<double>& targetStack, double pushNumber)
		: m_act(MC_Parser::token::NUMBER), m_pushNumber(pushNumber), m_stack(targetStack){}

	MC_Action(std::stack<double>& targetStack, MC::MC_Parser::token::yytokentype act)
		: m_act(act), m_pushNumber(0), m_stack(targetStack){}

	MC_Action& operator=(const MC_Action& other) 
	{
		m_pushNumber = other.m_pushNumber;
		m_act = other.m_act;
		m_stack = other.m_stack;
		return *this;
	}

	void action()
	{
		switch (m_act)
		{
			case MC_Parser::token::ADD:
				{
					double d1 = m_stack.top();m_stack.pop();
					double d2 = m_stack.top();m_stack.pop();

					std::cout << d2 << " + " << d1 << std::endl; 

					m_stack.push( d2 + d1);
				}
				break;

			case MC_Parser::token::MIN:
				{
					double d1 = m_stack.top();m_stack.pop();
					double d2 = m_stack.top();m_stack.pop();

					std::cout << d2 << " - " << d1 << std::endl; 

					m_stack.push( d2 - d1);
				}
				break;

			case MC_Parser::token::DIV:
				{
					double d1 = m_stack.top();m_stack.pop();
					double d2 = m_stack.top();m_stack.pop();

					std::cout << d2 << " / " << d1 << std::endl; 

					m_stack.push( d2 / d1);
				}
				break;

			case MC_Parser::token::MUL:
				{
					double d1 = m_stack.top();m_stack.pop();
					double d2 = m_stack.top();m_stack.pop();

					std::cout << d2 << " * " << d1 << std::endl; 

					m_stack.push( d2 * d1);
				}
				break;

			case MC_Parser::token::LOG:
				{
					double d1 = m_stack.top();m_stack.pop();

					std::cout << "log(" << d1 << ")" << std::endl;

					m_stack.push(log(d1));
				}
				break;

			case MC_Parser::token::NUMBER:
				{
					std::cout << "PushNumber " << m_pushNumber << std::endl; 
					m_stack.push(m_pushNumber);
				}

				break;
		}
	}
};

};


#endif // !MC_ACTION_INCLUDED
