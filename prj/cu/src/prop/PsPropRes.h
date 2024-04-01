#ifndef ___PS_PROP_RES__PH___
#define ___PS_PROP_RES__PH___

#include <PsCtlRes.h>

#define __IDD_PS_PRP		(__IDD_PS_CTL + 384)		/// 384
#define __IDR_PS_PRP		(__IDR_PS_CTL + 384)		/// 384

#define __IDI_PS_PRP		(__IDI_PS_CTL + 384)		/// 128	- Shares with __IDB_PS_PRP, __IDCR_PS_PRP
#define __IDB_PS_PRP		(__IDI_PS_PRP + 128)		/// 128	- Shares with __IDI_PS_PRP, __IDCR_PS_PRP
#define __IDCR_PS_PRP		(__IDB_PS_PRP + 128)		/// 128	- Shares with __IDI_PS_PRP, __IDB_PS_PRP

#define __IDS_PS_PRP		(__IDS_PS_CTL + 384)		/// 192	- Shares with __IDP_PS_PRP
#define __IDP_PS_PRP		(__IDS_PS_PRP + 192)		/// 192	- Shares with __IDS_PS_PRP

#define __ID_PS_PRP			(__ID_PS_CTL + 256)			/// 256

#define __IDC_PS_PRP		(__IDD_PS_CTL + 500)		/// 500

#endif //!___PS_PROP_RES__PH___