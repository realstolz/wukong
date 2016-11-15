/*
 * Copyright (c) 2016 Shanghai Jiao Tong University.
 *     All rights reserved.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing,
 *  software distributed under the License is distributed on an "AS
 *  IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 *  express or implied.  See the License for the specific language
 *  governing permissions and limitations under the License.
 *
 * For more about this software visit:
 *
 *      http://ipads.se.sjtu.edu.cn/projects/wukong.html
 *
 */

#pragma once

#include "network_node.h"
#include "rdma_resource.h"


struct thread_cfg {
	int sid;    // server id
	int wid;    // worker id

	// TODO: out of thread_cfg
	int nsrvs;  // #servers
	int nwkrs;  // #workers on each server
	int nswkrs; // #backend workers on each server
	int ncwkrs; // #frontend workers on each server

	Network_Node *node;  // communicaiton by TCP/IP
	RdmaResource *rdma;  // communicaiton by RDMA
	void *ptr;


	// Note that overflow of qid is innocent if there is no long-running
	// fork-join query. Because we use qid to recognize the owner sid
	// and wid, as well as collect the results of sub-queries.
	int qid;  // The ID of each (sub-)query

	unsigned int seed;

	void init(void) {
		qid = nwkrs * sid + wid;
		seed = qid;
	}

	unsigned get_random(void) {
		return rand_r(&seed);
	}

	int get_and_inc_qid(void) {
		int tmp = qid;
		qid += nsrvs * nwkrs;
		return tmp;
	}

	int sid_of(int qid) {
		return (qid % (nsrvs * nwkrs)) / nwkrs;
	}

	int wid_of(int qid) {
		return qid % nwkrs;
	}
};
