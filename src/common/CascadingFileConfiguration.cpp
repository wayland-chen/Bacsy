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

#include <fstream>
#include <functional>
#include <algorithm>
#include "Poco/Environment.h"
#include <Poco/String.h>
#include "common/StringUtils.h"
#include "common/CascadingFileConfiguration.h"
#include "rules/StringExclusionRuleBuilder.h"

namespace bacsy
{

CascadingFileConfiguration::CascadingFileConfiguration(const std::string& filename):
	inputStream(filename),
	configIsLoaded(inputStream),
	config(inputStream),
	globalSectionName("global")
{

}

bool CascadingFileConfiguration::toBool(const std::string& input)
{
	const std::string lowered = Poco::toLower(input);

	return (lowered == "true" || lowered == "1");
}

const ConfigurationFile& CascadingFileConfiguration::getConfig() const
{
	return storeConfig;
}

ConfigurationFile& CascadingFileConfiguration::getConfig()
{
	return storeConfig;
}

bool ConfigurationFile::isLoaded() const
{
	return iconfigIsLoaded;
}

}