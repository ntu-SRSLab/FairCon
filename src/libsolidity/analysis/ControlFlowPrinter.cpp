#include <libsolidity/analysis/ControlFlowPrinter.h>

#include <liblangutil/SourceLocation.h>
#include <libdevcore/Algorithms.h>
#include <boost/range/algorithm/sort.hpp>


using namespace std;
using namespace langutil;
using namespace dev::solidity;

void ControlFlowPrinter::print(ostream& _stream)
{
  m_ostream = &_stream;
	m_cfg.accept(*this);
  m_ostream = nullptr;
}

bool ControlFlowPrinter::visit(FunctionDefinition const& _function)
{
	if (_function.isImplemented())
	{
    if (_function.isConstructor())
      writeLine("Constructor: ()");
    else if (_function.isFallback())
      writeLine("Fallback: ()");
    else
      writeLine("Function: " + _function.externalSignature());

    auto const& functionFlow = m_cfg.functionFlow(_function);
		printFunctionFlow(functionFlow.entry);
	}
	return false;
}

void ControlFlowPrinter::printFunctionFlow(CFGNode const* _entry) const
{
  BreadthFirstSearch<CFGNode>{{_entry}}.run(
    [this](CFGNode const& _node, auto&& _addChild) {
      for (CFGNode const* exit: _node.exits) {
        this -> writeLine("(" + std::to_string(_node.location.start)
                  + "," + std::to_string(_node.location.end)
                  + ") ---> (" + std::to_string(exit->location.start)
                  + "," + std::to_string(exit->location.end) + ")");
        _addChild(*exit);
      }
    });
}

void ControlFlowPrinter::writeLine(string const& _line) const
{
	*m_ostream << _line << endl;
}

