// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.
// See the LICENSE file in the project root for more information.

// This file allows customization of the test strongname key used in place of the real MS key

#ifdef FEATURE_STRONGNAME_TESTKEY_ALLOWED

//
// #TestKeyStamping
// 
// On CoreCLR, we have a requirement that only keys signed with the Microsoft public key can be considered
// part of the platform and therefore contain critical code.  This leads to an issue with testing the
// product, since any tests which need to test platform only feautres would need to be signed  by the
// Microsoft public key, and for a variety of reasons it is not feasable to sign all of our test assemblies
// with that key.
// 
// Instead, we provide an extension where any assembly signed with the public key contained in the
// g_rbTestKeyBuffer will also be considered part of the platform.  The buffer is filled with a zero key,
// which means by default non-Microsoft signatures will not be accepted.  However, the slstampkey tool looks
// for the two GUIDs in the beginning of the buffer, and can replace the key with a real one of the test
// team's choosing.  Once this modification is in place, test assemblies can be considered part of the
// platform and can access critical APIs.
// 
// Since this buffer is searched for in the VM using external tools, it's very important that it only appear
// once in the final image of the runtime.  If it appears multiple times, tools will be unable to determine
// which test key buffer is the real buffer, and therefore tests which rely on containing platform code will
// be unable to run on the build.
// 

#define TEST_KEY_HEADER \
    /* Test key buffer header 1: { cd517db8-a1b1-44bf-aa64-bf66fefa3831 } */ \
    0xb8, 0x7d, 0x51, 0xcd, 0xb1, 0xa1, 0xbf, 0x44, 0x64, 0xaa, 0xbf, 0x66, 0xfe, 0xfa, 0x38, 0x31, \
    \
    /* Test key buffer header 2: { 5f363032-eaaf-4103-b312-ab2c8e35cf58 } */ \
    0x32, 0x30, 0x36, 0x5f, 0xaf, 0xea, 0x03, 0x41, 0x12, 0xb3, 0xab, 0x2c, 0x8e, 0x35, 0xcf, 0x58,

        
#define TEST_KEY_VALUE \
    /* SigAlgId = */\
    0x00, 0x24, 0x00, 0x00, \
    \
    /* HashAlgId = */\
    0x04, 0x80, 0x00, 0x00, \
    \
    /* cbPublicKey = 0x94 */ \
    0x94, 0x00, 0x00, 0x00, \
     \
    /* 1024 bit public key */ \
    0x06, 0x02, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x52, 0x53, 0x41, 0x31, 0x00, 0x04, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, \
    0x0f, 0xc5, 0x99, 0x3e, 0x0f, 0x51, 0x1a, 0xd5, 0xe1, 0x6e, 0x8b, 0x22, 0x65, 0x53, 0x49, 0x3e, 0x09, 0x06, 0x7a, 0xfc, \
    0x41, 0x03, 0x9f, 0x70, 0xda, 0xeb, 0x94, 0xa9, 0x68, 0xd6, 0x64, 0xf4, 0x0e, 0x69, 0xa4, 0x6b, 0x61, 0x7d, 0x15, 0xd3, \
    0xd5, 0x32, 0x8b, 0xe7, 0xdb, 0xed, 0xd0, 0x59, 0xeb, 0x98, 0x49, 0x5a, 0x3b, 0x03, 0xcb, 0x4e, 0xa4, 0xba, 0x12, 0x74, \
    0x44, 0x67, 0x1c, 0x3c, 0x84, 0xcb, 0xc1, 0xfd, 0xc3, 0x93, 0xd7, 0xe1, 0x0b, 0x5e, 0xe3, 0xf3, 0x1f, 0x5a, 0x29, 0xf0, \
    0x05, 0xe5, 0xee, 0xd7, 0xe3, 0xc9, 0xc8, 0xaf, 0x74, 0xf4, 0x13, 0xf0, 0x00, 0x4f, 0x0c, 0x2c, 0xab, 0xb2, 0x2f, 0x9d, \
    0xd4, 0xf7, 0x5a, 0x6f, 0x59, 0x97, 0x84, 0xe1, 0xba, 0xb7, 0x09, 0x85, 0xef, 0x81, 0x74, 0xca, 0x6c, 0x68, 0x42, 0x78, \
    0xbe, 0x82, 0xce, 0x05, 0x5a, 0x03, 0xeb, 0xaf

    //
    // Test Public key blob
    //

    //
    // No prestamped test key - create an empty key buffer
    //
#define TEST_KEY_BUFFER \
    /* SigAlgId */ \
    0x00, 0x00, 0x00, 0x00, \
    \
    /* HashAlgId */ \
    0x00, 0x00, 0x00, 0x00, \
    \
    /* cbPublicKey = 0x94 - this needs to match the size of the public key section below */ \
    0x94, 0x00, 0x00, 0x00, \
    \
    /* 1024 bit public key - 0x94 bytes */ \
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

#endif // FEATURE_STRONGNAME_TESTKEY_ALLOWED