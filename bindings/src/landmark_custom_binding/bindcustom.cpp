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

// CustomDataStruct

#include "bind_string_property_definitions.h"
#include "include/bindcustom.hpp"

namespace py = pybind11;

namespace pydeepstream {

    void * copy_custom_struct(void* data, void* user_data) {
        NvDsUserMeta * srcMeta = (NvDsUserMeta*) data;
        NvDsInferFaceLandmarkMeta * srcData = (NvDsInferFaceLandmarkMeta *) srcMeta->user_meta_data;
        NvDsInferFaceLandmarkMeta *destData = (NvDsInferFaceLandmarkMeta *) g_malloc0(
                        sizeof(NvDsInferFaceLandmarkMeta));

        destData->size = srcData->size;
        destData->num_landmark = srcData->num_landmark;
        destData->data = (gfloat*)g_malloc(srcData->size);
        memcpy(destData->data, srcData->data, srcData->size);

        return destData;
    }

    void release_custom_struct(void * data, void * user_data) {
        NvDsUserMeta * srcMeta = (NvDsUserMeta*) data;
        if (srcMeta != nullptr) {
            NvDsInferFaceLandmarkMeta * srcData = (NvDsInferFaceLandmarkMeta *) srcMeta->user_meta_data;
            if (srcData != nullptr) {
                if (srcData->data != nullptr)
                {
                    free(srcData->data);
                }
                g_free(srcData);
            }
        }
    }

    void bindcustom(py::module &m) {
        py::class_<NvDsInferFaceLandmarkMeta>(m, "NvDsInferFaceLandmarkMeta")
            .def(py::init<>())
            .def_readwrite("data", &NvDsInferFaceLandmarkMeta::data)
            .def_readwrite("size", &NvDsInferFaceLandmarkMeta::size)
            .def_readwrite("num_landmark", &NvDsInferFaceLandmarkMeta::num_landmark)
            .def("cast", [](void *data) {
                 return (NvDsInferFaceLandmarkMeta *) data;
             }, py::return_value_policy::reference);

        m.def("alloc_custom_struct",
              [](NvDsUserMeta *meta) {
                  auto *mem = (NvDsInferFaceLandmarkMeta *) g_malloc0(sizeof(NvDsInferFaceLandmarkMeta));
                  meta->base_meta.copy_func = (NvDsMetaCopyFunc) pydeepstream::copy_custom_struct;
                  meta->base_meta.release_func = (NvDsMetaReleaseFunc) pydeepstream::release_custom_struct;
                  return mem;
              },
              py::return_value_policy::reference);
    }

}