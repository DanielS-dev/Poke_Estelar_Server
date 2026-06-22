// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_RSA_H_C4E277DA8E884B578DDBF0566F504E91
#define FS_RSA_H_C4E277DA8E884B578DDBF0566F504E91

#include <gmp.h>

class RSA
{
	public:
		RSA();
		~RSA();

		// non-copyable
		RSA(const RSA&) = delete;
		RSA& operator=(const RSA&) = delete;

		void setKey(const char* pString, const char* qString);
		void decrypt(char* msg) const;

	private:
		//use only GMP
		mpz_t n, d;
};

#endif
