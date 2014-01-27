/**
* @file
*
* @section LICENSE
*
* OsmAnd - Android navigation software based on OSM maps.
* Copyright (C) 2010-2014  OsmAnd Authors listed in AUTHORS file
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

* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _OSMAND_CORE_MODEL_POSTCODE_AREA_H_
#define _OSMAND_CORE_MODEL_POSTCODE_AREA_H_

#include <OsmAndCore/QtExtensions.h>

#include <OsmAndCore.h>
#include <OsmAndCore/Data/Model/StreetGroup.h>

namespace OsmAnd {

    class ObfAddressSectionReader_P;

    namespace Model {

        class OSMAND_CORE_API PostcodeArea : public StreetGroup
        {
        private:
        protected:
            PostcodeArea();
        public:
            virtual ~PostcodeArea();

        friend class OsmAnd::ObfAddressSectionReader_P;
        };

    } // namespace Model

} // namespace OsmAnd

#endif // _OSMAND_CORE_MODEL_POSTCODE_AREA_H_
