/*
 * SPDX-FileCopyrightText: Copyright (c) 2021-2022 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 
#pragma once

namespace pydsdoc
{
    namespace custom
    {
        namespace NvDsInferFaceLandmarkMetaDoc
        {
            constexpr const char* descr = R"pyds(
                Represents face_landmark data used in DeepStream's NvDsInfer plugin.
                
                This structure is used to store the coordinates and other relevant information
                of detected landmarks on a face in a video frame.

                :ivar data: *gfloat pointer*, A pointer to an array of floating-point values representing
                            the coordinates of the face landmarks. The data is typically organized
                            as a sequence of (x, y) pairs.
                :ivar size: *guint*, The size of the `data` array, usually calculated as the number
                            of landmarks times the size of a float times 2 (for x and y coordinates).
                :ivar num_landmark: *guint*, The number of landmarks detected on the face.
                )pyds";

            constexpr const char* cast = R"pyds(
                Casts a given object/data to :class:`NvDsInferFaceLandmarkMeta`. 
                
                This is used to convert raw data obtained from DeepStream metadata into
                a structured `NvDsInferFaceLandmarkMeta` object for easier manipulation
                and access in Python.

                Usage: 
                ```python
                casted_data = pyds.NvDsInferFaceLandmarkMeta.cast(data)
                ```
                )pyds";
        }
    }
}
