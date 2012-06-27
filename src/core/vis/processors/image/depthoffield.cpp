/**********************************************************************
 *                                                                    *
 * Voreen - The Volume Rendering Engine                               *
 *                                                                    *
 * Copyright (C) 2005-2008 Visualization and Computer Graphics Group, *
 * Department of Computer Science, University of Muenster, Germany.   *
 * <http://viscg.uni-muenster.de>                                     *
 *                                                                    *
 * This file is part of the Voreen software package. Voreen is free   *
 * software: you can redistribute it and/or modify it under the terms *
 * of the GNU General Public License version 2 as published by the    *
 * Free Software Foundation.                                          *
 *                                                                    *
 * Voreen is distributed in the hope that it will be useful,          *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of     *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the       *
 * GNU General Public License for more details.                       *
 *                                                                    *
 * You should have received a copy of the GNU General Public License  *
 * in the file "LICENSE.txt" along with this program.                 *
 * If not, see <http://www.gnu.org/licenses/>.                        *
 *                                                                    *
 * The authors reserve all rights not expressly granted herein. For   *
 * non-commercial academic use see the license exception specified in *
 * the file "LICENSE-academic.txt". To get information about          *
 * commercial licensing please contact the authors.                   *
 *                                                                    *
 **********************************************************************/

//TODO: include the right headers
#include "voreen/core/vis/processors/image/depthoffield.h"
#include "voreen/core/vis/processors/portmapping.h"

#include "tgt/assert.h"
#include "tgt/glmath.h"
#include "tgt/vector.h"

#include "voreen/core/vis/voreenpainter.h"
#include "voreen/core/vis/messagedistributor.h"

namespace voreen {

//TODO: check if all of these are needed
using tgt::vec3;
using tgt::ivec2;
using tgt::Color;
using std::vector;

//---------------------------------------------------------------------------

const Identifier DepthOfField::setDepthOfFieldThreshold_("set.depthOfFieldThreshold");

DepthOfField::DepthOfField()
    : GenericFragment("pp_depthoffield"),
    depthThreshold_(setDepthOfFieldThreshold_, "Depth Threshold")
{
    setName("Depth of Field");
	addProperty(&depthThreshold_);

    createInport("image.inport");
    createOutport("image.outport");
}

const std::string DepthOfField::getProcessorInfo() const {
	return "Performs a depth of field rendering.";
}

void DepthOfField::setDepthThreshold(float depthThreshold) {
    depthThreshold_.set(depthThreshold);
}

void DepthOfField::process(LocalPortMapping* portMapping) {
    glViewport(0,0,(int)size_.x,(int)size_.y);

	int source = portMapping->getTarget("image.inport");
    int dest = portMapping->getTarget("image.outport");

	tc_->setActiveTarget(dest, "DepthOfField::process");

    analyzeDepthBuffer(source);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // bind shading result from previous ray cast
    glActiveTexture(tm_.getGLTexUnit(shadeTexUnit_));
    glBindTexture(tc_->getGLTexTarget(source), tc_->getGLTexID(source));
    LGL_ERROR;

    // bind depth result from previous ray cast
    glActiveTexture(tm_.getGLTexUnit(depthTexUnit_));
    glBindTexture(tc_->getGLDepthTexTarget(source), tc_->getGLDepthTexID(source));
    LGL_ERROR;

    // initialize shader
    program_->activate();
    setGlobalShaderParameters(program_);
    program_->setUniform("shadeTex_", (GLint) tm_.getTexUnit(shadeTexUnit_));
    program_->setUniform("depthTex_", (GLint) tm_.getTexUnit(depthTexUnit_));
    program_->setUniform("minDepth_", minDepth_.get());
    program_->setUniform("maxDepth_", maxDepth_.get());
    program_->setUniform("depthThreshold_", depthThreshold_.get());

    renderQuad();

    program_->deactivate();
    glActiveTexture(TexUnitMapper::getGLTexUnitFromInt(0));
    LGL_ERROR;
}


} // voreen namespace

