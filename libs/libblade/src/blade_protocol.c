/*
 * Copyright (c) 2017, Shane Bryldt
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * * Neither the name of the original author; nor the names of any contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 * 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "blade.h"

KS_DECLARE(ks_status_t) blade_request_create(blade_request_t **breqP, ks_pool_t *pool, const char *session_id, cJSON *json /*, response_callback*/)
{
	blade_request_t *breq = NULL;

	ks_assert(breqP);
	ks_assert(pool);
	ks_assert(session_id);
	ks_assert(json);

	breq = ks_pool_alloc(pool, sizeof(blade_request_t));
	breq->pool = pool;
	breq->refs = 1;
	breq->session_id = ks_pstrdup(pool, session_id);
	breq->message = json;
	breq->message_id = cJSON_GetObjectCstr(json, "id");
	//breq->response_callback = response_callback;
	*breqP = breq;

	return KS_STATUS_SUCCESS;
}

KS_DECLARE(ks_status_t) blade_request_destroy(blade_request_t **breqP)
{
	blade_request_t *breq = NULL;

	ks_assert(breqP);
	ks_assert(*breqP);

	breq = *breqP;

	ks_pool_free(breq->pool, (void **)&breq->session_id);
	cJSON_Delete(breq->message);

	ks_pool_free(breq->pool, breqP);

	return KS_STATUS_SUCCESS;
}


/* For Emacs:
 * Local Variables:
 * mode:c
 * indent-tabs-mode:t
 * tab-width:4
 * c-basic-offset:4
 * End:
 * For VIM:
 * vim:set softtabstop=4 shiftwidth=4 tabstop=4 noet:
 */