/*
 * Copyright (c) 2016 Sebastian Weber, Henri Menke. All rights reserved.
 *
 * This file is part of the pairinteraction library.
 *
 * The pairinteraction library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The pairinteraction library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with the pairinteraction library. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DTYPES_H
#define DTYPES_H

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <array>
#include <cmath>
#include <unsupported/Eigen/CXX11/Tensor>
#include <vector>

typedef std::complex<double> complex_t;
typedef uint32_t idx_t;
typedef double storage_double; // TODO has always to be the same as double
typedef int32_t storage_idx_t;

typedef uint8_t byte_t;
typedef std::vector<byte_t> bytes_t;
typedef std::nullptr_t invalid_t;

#ifdef USE_COMPLEX
typedef complex_t scalar_t;
#else
typedef double scalar_t;
#endif

typedef Eigen::Triplet<scalar_t> eigen_triplet_t;
typedef Eigen::Triplet<complex_t> eigen_triplet_complex_t;
typedef Eigen::Triplet<double> eigen_triplet_double_t;
typedef Eigen::SparseMatrix<scalar_t> eigen_sparse_t;
typedef Eigen::SparseMatrix<double> eigen_sparse_double_t;
typedef Eigen::SparseMatrix<complex_t> eigen_sparse_complex_t;
typedef Eigen::SparseMatrix<scalar_t>::InnerIterator eigen_iterator_t;
typedef Eigen::SparseMatrix<double>::InnerIterator eigen_iterator_double_t;
typedef Eigen::SparseMatrix<complex_t>::InnerIterator eigen_iterator_complex_t;
typedef Eigen::Matrix<scalar_t, Eigen::Dynamic, Eigen::Dynamic> eigen_dense_t;
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> eigen_dense_double_t;
typedef Eigen::Matrix<scalar_t, Eigen::Dynamic, 1> eigen_vector_t;
typedef Eigen::Matrix<double, Eigen::Dynamic, 1> eigen_vector_double_t;

typedef Eigen::Matrix<double, 3, 3> eigen_matrix33;
typedef Eigen::TensorFixedSize<double, Eigen::Sizes<3, 3, 3>> eigen_tensor333;

constexpr const double au2GHz = 6579683.920757349;
constexpr const double au2Vcm = 5142206707.0;
constexpr const double au2G = 2350517550.0;
constexpr const double au2um = 5.2917721067e-05;
constexpr const double inverse_electric_constant = au2Vcm * au2Vcm * au2um * au2um * au2um / au2GHz;
constexpr const double sqrt_inverse_electric_constant =
    0.7717003798774048; // equals sqrt(inverse_electric_constant)
constexpr const double inverse_electron_rest_mass = au2Vcm * au2Vcm / au2G / au2G / au2GHz;

constexpr const double coulombs_constant = au2Vcm * au2Vcm * au2um * au2um * au2um / au2GHz;
constexpr const double electron_rest_mass = au2G * au2G * au2GHz / au2Vcm / au2Vcm;
constexpr const double elementary_charge = au2GHz / au2um / au2Vcm;
constexpr const double bohr_magneton = 0.5 * au2GHz / au2G;
constexpr const double reduced_planck_constant = au2GHz * au2um * au2G / au2Vcm;
constexpr const double speed_of_light = 137.035999139 * au2Vcm / au2G;

constexpr const double muB = 0.5; // in atomic units
constexpr const double gS = 2.0023192;
constexpr const double gL = 1;

constexpr const int ARB = 32767;

#ifdef WITH_INTEL_MKL
constexpr const bool mkl_enabled = true;
#else  // WITH_INTEL_MKL
constexpr const bool mkl_enabled = false;
#endif // WITH_INTEL_MKL

#ifdef WITH_GSL
constexpr const bool gsl_enabled = true;
#else  // WITH_GSL
constexpr const bool gsl_enabled = false;
#endif // WITH_GSL

enum parity_t {
    NA = INT_MAX,
    EVEN = 1,
    ODD = -1,
};

enum method_t {
    NUMEROV = 0,
    WHITTAKER = 1,
};

struct Symmetry {
    parity_t inversion;
    parity_t reflection;
    parity_t permutation;
    int rotation;

    // Comparison operator that is needed if an object of type Symmetry is used as key for std::map
    friend bool operator<(const Symmetry &s1, const Symmetry &s2) {
        std::array<int, 5> syms1{{s1.inversion, s1.reflection, s1.permutation, s1.rotation}};
        std::array<int, 5> syms2{{s2.inversion, s2.reflection, s2.permutation, s2.rotation}};

        for (size_t i = 0; i < syms1.size(); ++i) {
            if (syms1[i] < syms2[i]) {
                return true;
            }
            if (syms1[i] > syms2[i]) {
                return false;
            }
        }
        return false;
    }
};

#endif
