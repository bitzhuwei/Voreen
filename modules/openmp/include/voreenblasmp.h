/***********************************************************************************
 *                                                                                 *
 * Voreen - The Volume Rendering Engine                                            *
 *                                                                                 *
 * Copyright (C) 2005-2012 University of Muenster, Germany.                        *
 * Visualization and Computer Graphics Group <http://viscg.uni-muenster.de>        *
 * For a list of authors please refer to the file "CREDITS.txt".                   *
 *                                                                                 *
 * This file is part of the Voreen software package. Voreen is free software:      *
 * you can redistribute it and/or modify it under the terms of the GNU General     *
 * Public License version 2 as published by the Free Software Foundation.          *
 *                                                                                 *
 * Voreen is distributed in the hope that it will be useful, but WITHOUT ANY       *
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR   *
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.      *
 *                                                                                 *
 * You should have received a copy of the GNU General Public License in the file   *
 * "LICENSE.txt" along with this file. If not, see <http://www.gnu.org/licenses/>. *
 *                                                                                 *
 * For non-commercial academic use see the license exception specified in the file *
 * "LICENSE-academic.txt". To get information about commercial licensing please    *
 * contact the authors.                                                            *
 *                                                                                 *
 ***********************************************************************************/

#ifndef VRN_VOREENBLASMP_H
#define VRN_VOREENBLASMP_H

#include "voreen/core/voreenmodule.h"
#include "voreen/core/utils/voreenblas/voreenblas.h"

namespace voreen {

/**
 * OpenMP implementation of the Basic Linear Algebra Subprograms (BLAS).
 */
class VoreenBlasMP : public VoreenBlas {

public:
    virtual void sAXPY(size_t vecSize, const float* vecx, const float* vecy, float alpha, float* result) const;

    virtual float sDOT(size_t vecSize, const float* vecx, const float* vecy) const;

    virtual float sNRM2(size_t vecSize, const float* vecx) const;

    virtual void sSpMVEll(const EllpackMatrix<float>& mat, const float* vec, float* result) const;

    virtual void hSpMVEll(const EllpackMatrix<int16_t>& mat, const float* vec, float* result) const;

    virtual float sSpInnerProductEll(const EllpackMatrix<float>& mat, const float* vecx, const float* vecy) const;

    virtual int sSpConjGradEll(const EllpackMatrix<float>& mat, const float* vec, float* result,
        float* initial = 0, ConjGradPreconditioner precond = NoPreconditioner, float threshold = 1e-4f, int maxIterations = 1000) const;

    virtual int hSpConjGradEll(const EllpackMatrix<int16_t>& mat, const float* vec, float* result,
        float* initial = 0, float threshold = 1e-4f, int maxIterations = 1000) const;

private:
    static const std::string loggerCat_; ///< category used in logging
};

} // namespace

#endif