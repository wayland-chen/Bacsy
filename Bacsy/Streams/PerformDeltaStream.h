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

#ifndef BACSY_PERFORM_DELTA_STREAM_H
#define BACSY_PERFORM_DELTA_STREAM_H

#include "Bacsy/Streams/RsyncStream.h"

namespace Bacsy
{
namespace Streams
{

using namespace Common;


class PerformDeltaStream : public RsyncStream<1024>
{
	public:
		PerformDeltaStream(SimpleOStream& ostream, rs_signature_t* signature);

};

}
}

#endif
