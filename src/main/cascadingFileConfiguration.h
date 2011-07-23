/*
 * Copyright (C) 2011  Ives van der Flaas
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CASCADING_FILE_CONFIGURATION
#define CASCADING_FILE_CONFIGURATION

#include <list>
#include <fstream>
#include <limits>
#include <string>
#include "woodcutter/woodcutter.h"
#include "configurationFile.h"


class CascadingFileConfiguration
{
	public:
		CascadingFileConfiguration(const std::string& directory);

		std::list<std::string> getTargets() const;
		std::vector<std::string> getIncludes(const std::string& target) const;
		std::vector<std::string> getExcludes(const std::string& target) const;
		unsigned int getPriority(const std::string& target) const;
		unsigned int getMinBackups(const std::string& target) const;
		unsigned int getMaxBackups(const std::string& target) const;
		std::string getPreferredOrder(const std::string& target) const;
		std::string getDistribution(const std::string& target) const;
		std::string getTimerString(const std::string& target) const;

	private:
		template<typename T>
		T getCascadingValue( 
				const std::string& section,
				const std::string& keyname, 
				const T& defaultValue = T()) const
		{
			T rv = defaultValue;

			rv = targetConfig.get<T>(globalSectionName, keyname, rv);
			rv = targetConfig.get<T>(section, keyname, rv);

			return rv;
		}

		std::ifstream inputTargetStream;	
		ConfigurationFile targetConfig;
		const std::string globalSectionName;
};

#endif
