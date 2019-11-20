#pragma once

#include <functional>

#define SCOPEGUARD_LINENAME2(name, line) name##line
#define SCOPEGUARD_LINENAME(name, line) SCOPEGUARD_LINENAME2(name, line)

#define SCOPE_EXIT(callback) ScopeGuard SCOPEGUARD_LINENAME(sgExit, __LINE__)(callback)

class ScopeGuard
{
public:
	/*explicit */ScopeGuard(std::function<void()> fnExitScope)
		: m_fnExitScope(fnExitScope), m_bDismissed(false)
	{ }

	~ScopeGuard()
	{
		if(!m_bDismissed)
		{
			m_fnExitScope();
		}
	}

	void Dismiss()
	{
		m_bDismissed = true;
	}

private:
	std::function<void()> m_fnExitScope;
	bool m_bDismissed;

private:
	ScopeGuard(ScopeGuard const&);
	ScopeGuard& operator=(ScopeGuard const&);
};