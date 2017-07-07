#pragma once

#include <string>

namespace btf
{
	class Error
	{
	public:
		Error(const std::string& message)
		{
			this->message = message;
		}

		std::string what() const
		{
			return message;
		}

	private:
		std::string message;
	};
}
