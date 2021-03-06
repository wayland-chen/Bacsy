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

#include <string>
#include "Bacsy/Common/StringUtils.h"
#include "Bacsy/Rules/SizeExclusionSubRule.h"

namespace Bacsy
{
namespace Rules
{

using namespace Common;


SizeExclusionSubRule::SizeExclusionSubRule(const Poco::File::FileSize sizeInBytes, const Operator theOperator, bool negated):
	ExclusionSubRule(negated),
	sizeInBytes(sizeInBytes),
	theOperator(theOperator)
{
}

bool SizeExclusionSubRule::matchWithoutNegate(const IFile& inputFile)
{
	if(!inputFile.isFile())
	{
		return false;
	}

	if(theOperator == LESS_THAN)
		return inputFile.getSize() < sizeInBytes;
	else
		return inputFile.getSize() > sizeInBytes;
}

ExclusionSubRule* SizeExclusionSubRule::clone() const
{
	return new SizeExclusionSubRule(*this);
}

SizeExclusionSubRule::SizeExclusionSubRule(const SizeExclusionSubRule& copy):
	ExclusionSubRule(copy.getNegated()),
	sizeInBytes(copy.sizeInBytes),
	theOperator(copy.theOperator)
{
	
}

Poco::File::FileSize SizeExclusionSubRule::getSizeInBytes() const
{
	return sizeInBytes;
}

SizeExclusionSubRule::Operator SizeExclusionSubRule::getOperator() const
{
	return theOperator;
}

}
}
