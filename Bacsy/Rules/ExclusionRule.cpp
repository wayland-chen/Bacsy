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
#include "woodcutter/woodcutter.h"
#include "Bacsy/Common/Utils.h"
#include "Bacsy/Common/StringUtils.h"
#include "Bacsy/Rules/ExclusionRule.h"

namespace Bacsy
{
namespace Rules
{

using namespace Common;


ExclusionRule::ExclusionRule(const ExclusionRule& rule)
{
	operator=(rule);
}

ExclusionRule::ExclusionRule()
{
}

ExclusionRule::~ExclusionRule()
{
	deleteSubRules();
}

bool ExclusionRule::match(const IFile& inputFile) const
{
	// Rules with no subrules match nothing by definition. Used for a full
	// file run by Source.
	if(subRules.size() == 0)
	{
		return false;
	}

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
void ExclusionRule::deleteSubRules()
{
	std::for_each(subRules.begin(), subRules.end(), ObjectDeleter());
	subRules.clear();
}

ExclusionRule& ExclusionRule::operator=(const ExclusionRule& rule)
{
	if(&rule == this)
		return *this;

	deleteSubRules();

	for(std::list<ExclusionSubRule*>::const_iterator it = rule.subRules.begin();
			it != rule.subRules.end();
			++it)
	{
		addSubRule((*it)->clone());
	}

	return *this;
}

void ExclusionRule::addSubRule(ExclusionSubRule* sr)
{
	subRules.push_back(sr);
}

const std::list<ExclusionSubRule*>& ExclusionRule::getSubRules() const
{
	return subRules;
}

std::string ExclusionRule::toString() const 
{
	std::string rv = "Rule with " + StringUtils::toString(subRules.size()) + " subrules: ";

	for(std::list<ExclusionSubRule*>::const_iterator it = subRules.begin();
			it != subRules.end();
			++it)
	{
		rv += (*it)->toString();
	}

	return rv;
}

}
}
