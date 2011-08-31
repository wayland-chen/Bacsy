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

#include <algorithm>
#include "Utils.h"
#include "ExclusionRule.h"

namespace bacsy
{

ExclusionRule::ExclusionRule(const ExclusionRule& rule)
{
	for(std::list<ExclusionSubRule*>::const_iterator it = rule.subRules.begin();
			it != rule.subRules.end();
			++it)
	{
		addSubRule((*it)->clone());
	}
}

ExclusionRule::ExclusionRule()
{
}

ExclusionRule::~ExclusionRule()
{
	std::for_each(subRules.begin(), subRules.end(), ObjectDeleter());
}

bool ExclusionRule::match(const Poco::File& inputFile) const
{
	for(std::list<ExclusionSubRule*>::const_iterator it = subRules.begin();
			it != subRules.end();
			++it)
	{
		if(!(*it)->match(inputFile))
		{
			return false;
		}
	}

	return true;
}

void ExclusionRule::addSubRule(ExclusionSubRule* sr)
{
	subRules.push_back(sr);
}

}
