/*
 * SPDX-FileCopyrightText: Copyright (c) 2022 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// NvDsInferFaceLandmarkMeta

#include "bind_string_property_definitions.h"
#include "include/bindcustom.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>
#include <cstring>

namespace py = pybind11;

namespace pydeepstream {

    void * copy_custom_struct(void* data, void* user_data) {
        NvDsUserMeta * srcMeta = (NvDsUserMeta*) data;
        NvDsInferFaceLandmarkMeta * srcData = (NvDsInferFaceLandmarkMeta *) srcMeta->user_meta_data;
        NvDsInferFaceLandmarkMeta *destData = (NvDsInferFaceLandmarkMeta *) malloc(sizeof(NvDsInferFaceLandmarkMeta));

        destData->num_landmark = srcData->num_landmark;
        destData->data = (float*) malloc(srcData->num_landmark * 2 * sizeof(float));
        memcpy(destData->data, srcData->data, srcData->num_landmark * 2 * sizeof(float));

        return destData;
    }

    void release_custom_struct(void * data, void * user_data) {
        NvDsUserMeta * srcMeta = (NvDsUserMeta*) data;
        if (srcMeta != nullptr) {
            NvDsInferFaceLandmarkMeta * srcData = (NvDsInferFaceLandmarkMeta *) srcMeta->user_meta_data;
            if (srcData != nullptr) {
                if (srcData->data != nullptr) {
                    free(srcData->data);
                }
                free(srcData);
            }
        }
    }

    void bindcustom(py::module &m) {
        py::class_<NvDsInferFaceLandmarkMeta>(m, "NvDsInferFaceLandmarkMeta")
            .def(py::init<>())
            .def_readwrite("num_landmark", &NvDsInferFaceLandmarkMeta::num_landmark)
            .def("cast", [](void *data) {
                 return (NvDsInferFaceLandmarkMeta *) data;
             }, py::return_value_policy::reference)
            .def("set_landmark_data", [](NvDsInferFaceLandmarkMeta &meta, const std::vector<float> &landmarks) {
                if (meta.data != nullptr) {
                    std::cout << "freeing meta.data" << std::endl;
                    free(meta.data); // 메모리 해제
                }
                std::cout << "landmarks.size(): " << landmarks.size() << std::endl;
                meta.data = (float*) malloc(landmarks.size() * sizeof(float));
                std::copy(landmarks.begin(), landmarks.end(), meta.data);
            })
            .def("get_landmark_data", [](const NvDsInferFaceLandmarkMeta &meta) {
                return std::vector<float>(meta.data, meta.data + meta.num_landmark * 2);
            });

        m.def("alloc_custom_struct",
              [](NvDsUserMeta *meta) {
                  auto *mem = (NvDsInferFaceLandmarkMeta *) malloc(sizeof(NvDsInferFaceLandmarkMeta));
                  meta->base_meta.copy_func = (NvDsMetaCopyFunc) pydeepstream::copy_custom_struct;
                  meta->base_meta.release_func = (NvDsMetaReleaseFunc) pydeepstream::release_custom_struct;
                  return mem;
              },
              py::return_value_policy::reference);
    }

}