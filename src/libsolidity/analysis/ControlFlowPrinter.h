#pragma once

#include <libsolidity/analysis/ControlFlowGraph.h>
#include <set>

namespace dev
{
namespace solidity
{
  
class ControlFlowPrinter: private CFGConstVisitor
{
public:
  
	explicit ControlFlowPrinter(CFG const& _cfg):
		m_cfg(_cfg) {}

	void print(std::ostream& _stream);
	bool visit(FunctionDefinition const& _function) override;

private:
	/// Checks for uninitialized variable accesses in the control flow between @param _entry and @param _exit.
	void printFunctionFlow(CFGNode const* _entry) const;
  void writeLine(std::string const& _line) const;
  
	CFG const& m_cfg;
  std::ostream* m_ostream = nullptr;
};

}
}
