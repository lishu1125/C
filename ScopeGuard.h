#ifndef LSLIB_SCOPEGUARD_H_
#define LSLIB_SCOPEGUARD_H_

#include <algorithm>
#include <functional>

namespace LsLib
{
	class ScopeGuard
	{
	public:
		explicit ScopeGuard(std::function<void()> onExitScope)
			: _onExitScope(onExitScope)
			, _dismissed(false)
		{
		}
		
		~ScopeGuard()
		{
			if (!_dismissed)
			{
				_onExitScope();
			}
		}

		void Dismiss()
		{
			_dismissed = true;
		}

	private:
		std::function<void()> _onExitScope;
		//允许调用者选择可跳过执行onExitScope();
		bool _dismissed;

	private:
		//noncopyable
		ScopeGuard(ScopeGuard const&) = delete;
		ScopeGuard& operator=(ScopeGuard const&) = delete;
	};
}

#define SCOPEGUARD_LINENAME_CAT(name, line) name##line
#define SCOPEGUARD_LINENAME(name, line) SCOPEGUARD_LINENAME_CAT(name, line)
#define ON_SCOPE_EXIT(callback) LsLib::ScopeGuard SCOPEGUARD_LINENAME(EXIT, __LINE__)(callback)

#endif
