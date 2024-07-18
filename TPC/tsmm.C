#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

#include "canvas/Utilities/InputTag.h"
#include "gallery/Event.h"

#include "TFile.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TGraph.h"
#include "TH1D.h"
#include "TStyle.h"
#include "TColor.h"
#include "TMath.h"
#include "TVectorT.h"
#include "TCanvas.h"
#include "lardataobj/RawData/RawDigit.h"
#include "TLegend.h"
#include <vector>
#include <set>
#include "Riostream.h"
#include "TString.h"
#include "TH1F.h"
#include "TProfile.h"
#include "TStyle.h"
#include "TROOT.h"

using namespace art;
using namespace std;


void tsmm()
{
  std::string inputtag="daq";
  InputTag rdts_tag{ inputtag };
  vector<string> filenames;
  TCanvas *mycanvas = (TCanvas*) new TCanvas("c1","",1000,500);
  mycanvas->SetLogy();
  
  TProfile *tsdiff = (TProfile*) new TProfile("tsdiff",";event;TSmax - TSmin (us)",8000,-0.5,7999.5);
  
    filenames.push_back("decode_data_evb01_run12804_10_20240424T093645-2381db31-e862-4140-b5ee-852a0008205f.root");
    filenames.push_back("decode_data_evb01_run12804_10_20240424T093650-9a8dd777-2e80-416c-ad0f-7f5c6c9f8bba.root");
    filenames.push_back("decode_data_evb01_run12804_10_20240424T093654-50c90c58-6863-498f-92f0-82e08db75276.root");
    filenames.push_back("decode_data_evb01_run12804_10_20240424T093659-b588cc5c-8ca7-472e-82f7-cffa7058efb0.root");
    filenames.push_back("decode_data_evb01_run12804_11_20240424T094230-5e87b9e6-917b-4c3c-9a4b-426338d4b24d.root");
    filenames.push_back("decode_data_evb01_run12804_11_20240424T094236-5e8a3f3c-c005-4b03-9b88-289fcc9062dd.root");
    filenames.push_back("decode_data_evb01_run12804_11_20240424T094242-52b90abe-c85c-4b10-b65d-48ac751e916a.root");
    filenames.push_back("decode_data_evb01_run12804_11_20240424T094248-9643b563-843c-46ce-b3fd-f3bde4ae6feb.root");
    filenames.push_back("decode_data_evb01_run12804_1_20240424T084121-5efdbae1-8da4-4861-a6be-8c4891a97982.root");
    filenames.push_back("decode_data_evb01_run12804_1_20240424T084122-9e042ac8-ad12-4bf7-a737-88ac39912056.root");
    filenames.push_back("decode_data_evb01_run12804_1_20240424T084129-3b396f0c-68e6-46fc-9b2b-88be889b8c43.root");
    filenames.push_back("decode_data_evb01_run12804_1_20240424T084134-41676b94-85da-4769-a836-be3b7e8920c3.root");
    filenames.push_back("decode_data_evb01_run12804_12_20240424T094830-27b39c54-3a4e-4744-b9ff-1831613e6031.root");
    filenames.push_back("decode_data_evb01_run12804_12_20240424T094835-1fd0fb04-c8fe-4942-a6aa-0f4d7d000c33.root");
    filenames.push_back("decode_data_evb01_run12804_12_20240424T094841-4a49477f-b3bd-44fc-a561-1845035e4823.root");
    filenames.push_back("decode_data_evb01_run12804_12_20240424T094846-a1aee8cb-4c37-44ea-9af8-365219e0d0e1.root");
    filenames.push_back("decode_data_evb01_run12804_13_20240424T095410-603ecb1f-06d9-424b-8040-6b1b318ce14a.root");
    filenames.push_back("decode_data_evb01_run12804_13_20240424T095414-d8d4e4dc-2e00-451c-9c59-a5aeb24b0369.root");
    filenames.push_back("decode_data_evb01_run12804_13_20240424T095418-33b5e4e4-fb67-49c5-9eae-02a4dc8910bc.root");
    filenames.push_back("decode_data_evb01_run12804_13_20240424T095424-1dcfa0df-f75f-4a14-9c52-5cf7917fd56c.root");
    filenames.push_back("decode_data_evb01_run12804_14_20240424T100002-f8fa9fb3-3bb3-4836-8692-505e0aee3662.root");
    filenames.push_back("decode_data_evb01_run12804_14_20240424T100006-db235d14-ad05-456b-9880-0065c695f9dd.root");
    filenames.push_back("decode_data_evb01_run12804_14_20240424T100009-494af8b2-f8c4-48c0-8920-42ee0033ddc3.root");
    filenames.push_back("decode_data_evb01_run12804_14_20240424T100014-ad1070bb-f676-46d3-afec-7995f9ac4d70.root");
    filenames.push_back("decode_data_evb01_run12804_15_20240424T100542-38ecc43c-988d-444f-b1a4-d2929079349a.root");
    filenames.push_back("decode_data_evb01_run12804_15_20240424T100548-a3664799-45f9-4353-baef-8a22f4fbf7da.root");
    filenames.push_back("decode_data_evb01_run12804_15_20240424T100554-309b052a-7ba3-45ec-a6ca-fc3c9cca0404.root");
    filenames.push_back("decode_data_evb01_run12804_15_20240424T100600-97b6224d-ca9c-4821-a600-23dc1a02c52d.root");
    filenames.push_back("decode_data_evb01_run12804_16_20240424T101228-bb5ad2e7-e676-4e6c-90ca-2889b8dc3919.root");
    filenames.push_back("decode_data_evb01_run12804_16_20240424T101234-988772b0-25fa-4366-992a-8f909f46eb09.root");
    filenames.push_back("decode_data_evb01_run12804_16_20240424T101240-98014fd1-d683-4e4f-8e39-a48a3ee9afe4.root");
    filenames.push_back("decode_data_evb01_run12804_16_20240424T101246-25a8e968-b903-4d5e-a2cf-b17b48479ee3.root");
    filenames.push_back("decode_data_evb01_run12804_17_20240424T101848-fe590ac6-0e36-4977-b667-e1f9c5d966a6.root");
    filenames.push_back("decode_data_evb01_run12804_17_20240424T101854-a854efc9-583d-4226-89c5-05a4d9393cc0.root");
    filenames.push_back("decode_data_evb01_run12804_17_20240424T101859-77785f52-6e64-4d11-b3ee-b82116382e0b.root");
    filenames.push_back("decode_data_evb01_run12804_17_20240424T101902-33b8bf70-0a94-4c20-945b-7b05eea18c17.root");
    filenames.push_back("decode_data_evb01_run12804_18_20240424T102441-8eaed329-447a-4445-9ae8-b428d51307fc.root");
    filenames.push_back("decode_data_evb01_run12804_18_20240424T102444-acef1f7f-d8cf-46eb-9f40-9b8502a3eb67.root");
    filenames.push_back("decode_data_evb01_run12804_18_20240424T102448-6515e90f-d639-46a8-aa04-6308a99b792c.root");
    filenames.push_back("decode_data_evb01_run12804_18_20240424T102452-af5e424d-4490-4d2c-b673-ff006c665cea.root");
    filenames.push_back("decode_data_evb01_run12804_19_20240424T103140-79c40b11-8574-401b-92af-b4f2a44b4329.root");
    filenames.push_back("decode_data_evb01_run12804_19_20240424T103144-4466d9c4-0d49-40c5-8c65-af1033b5e19f.root");
    filenames.push_back("decode_data_evb01_run12804_19_20240424T103148-8d487083-b200-4223-b552-a12c030cbb05.root");
    filenames.push_back("decode_data_evb01_run12804_19_20240424T103152-562a9482-7204-4eae-a586-a64485555833.root");
    filenames.push_back("decode_data_evb01_run12804_20_20240424T103734-5f1dd6bd-6245-41cb-bdde-f5895209149a.root");
    filenames.push_back("decode_data_evb01_run12804_20_20240424T103738-7d9a898b-5530-4a69-9412-8137efdb0117.root");
    filenames.push_back("decode_data_evb01_run12804_20_20240424T103743-0e6fbef6-ce3e-4b02-b87d-f0786e6d9ddc.root");
    filenames.push_back("decode_data_evb01_run12804_20_20240424T103746-d3a212ac-dd50-46f9-867b-56a170bc78f4.root");
    filenames.push_back("decode_data_evb01_run12804_21_20240424T104302-02bd2af8-79ec-4ac8-8f6c-42a70506d8d0.root");
    filenames.push_back("decode_data_evb01_run12804_21_20240424T104305-7616ff6e-a5be-46ae-84b3-9d659f56f3ba.root");
    filenames.push_back("decode_data_evb01_run12804_21_20240424T104309-e5306dff-6ccc-4a6a-91d0-0198e3801f9c.root");
    filenames.push_back("decode_data_evb01_run12804_21_20240424T104312-089370f3-10c2-406e-9467-e1542f27fdcf.root");
    filenames.push_back("decode_data_evb01_run12804_2_20240424T084659-e140fcfd-eec3-4638-913a-81bc53dbacfc.root");
    filenames.push_back("decode_data_evb01_run12804_2_20240424T084705-fd7664ad-e83c-4e0c-a178-83ffb84b75df.root");
    filenames.push_back("decode_data_evb01_run12804_2_20240424T084711-1c9895ef-701e-4a1c-a33e-fb479e502022.root");
    filenames.push_back("decode_data_evb01_run12804_2_20240424T084717-793c282a-103d-4b52-8fa6-de0157e1c2f6.root");
    filenames.push_back("decode_data_evb01_run12804_22_20240424T104900-17a866f4-1e9e-4f63-a4c2-496da828aa5d.root");
    filenames.push_back("decode_data_evb01_run12804_22_20240424T104903-faf00a94-1b96-47ff-a381-825e11636042.root");
    filenames.push_back("decode_data_evb01_run12804_22_20240424T104908-c3b7a854-4420-4306-b67c-eb2f5eb585d3.root");
    filenames.push_back("decode_data_evb01_run12804_22_20240424T104913-1e1f1787-8cfa-464c-b5f7-faad4c50ca11.root");
    filenames.push_back("decode_data_evb01_run12804_23_20240424T105505-51eadb6a-0970-4a60-9cc5-d0194b9552ce.root");
    filenames.push_back("decode_data_evb01_run12804_23_20240424T105510-4be91dca-37cd-43c3-9e73-148cd4767e91.root");
    filenames.push_back("decode_data_evb01_run12804_23_20240424T105514-42be56ba-c36e-4af2-b21c-17db68989908.root");
    filenames.push_back("decode_data_evb01_run12804_23_20240424T105520-aef70b5c-092b-4e98-9232-4dba07695a0b.root");
    filenames.push_back("decode_data_evb01_run12804_24_20240424T110110-e77d6cc4-4d71-47ae-ab93-69c9f11cb5a1.root");
    filenames.push_back("decode_data_evb01_run12804_24_20240424T110116-7ca1695b-731d-40ed-81f8-d8369ebbf65e.root");
    filenames.push_back("decode_data_evb01_run12804_24_20240424T110122-6c41feb1-eaa9-444a-ada4-aeb23a3036ad.root");
    filenames.push_back("decode_data_evb01_run12804_24_20240424T110127-2b4f1def-2ac3-4ae6-9a43-ffc0e3dae68d.root");
    filenames.push_back("decode_data_evb01_run12804_25_20240424T110649-a2a10baa-330e-47a3-9215-ebfc1eb8b640.root");
    filenames.push_back("decode_data_evb01_run12804_25_20240424T110652-978f62ee-1234-41d3-a76f-b6ab9a38d3ae.root");
    filenames.push_back("decode_data_evb01_run12804_25_20240424T110656-6a5841f7-805b-4240-9ce3-0a5540a97325.root");
    filenames.push_back("decode_data_evb01_run12804_25_20240424T110659-1e886b85-fbd3-4c62-b22f-808ad85effcf.root");
    filenames.push_back("decode_data_evb01_run12804_26_20240424T111210-97bb8623-13c6-4b28-85bb-df6758976347.root");
    filenames.push_back("decode_data_evb01_run12804_26_20240424T111216-89cd58f3-a294-4696-a32a-71fdb9a3cb9f.root");
    filenames.push_back("decode_data_evb01_run12804_26_20240424T111222-d5e46e18-f746-4d6f-8cf3-678b7382a059.root");
    filenames.push_back("decode_data_evb01_run12804_26_20240424T111228-cfad82f2-9c43-4217-b54e-939f149c262f.root");
    filenames.push_back("decode_data_evb01_run12804_27_20240424T111842-52fb5d85-a3a1-48e1-bf2f-6f0e18558dd5.root");
    filenames.push_back("decode_data_evb01_run12804_27_20240424T111846-d0b94946-25f4-4b42-868f-2d2e5578b399.root");
    filenames.push_back("decode_data_evb01_run12804_27_20240424T111850-99c5a6a7-acaf-473a-918e-18952a8bab82.root");
    filenames.push_back("decode_data_evb01_run12804_27_20240424T111854-cfd8295e-1e8f-4242-914c-4ac255303e2d.root");
    filenames.push_back("decode_data_evb01_run12804_28_20240424T112426-1ead5ed4-bb35-4a81-a02c-aeec5ffbecfd.root");
    filenames.push_back("decode_data_evb01_run12804_28_20240424T112431-796b90b0-e29f-462e-993a-0d81300f2aa6.root");
    filenames.push_back("decode_data_evb01_run12804_28_20240424T112434-ec2e802d-5ca2-421c-8b75-2138baeb0e47.root");
    filenames.push_back("decode_data_evb01_run12804_28_20240424T112439-38d2aa4e-2309-4070-a09d-9b8afe386094.root");
    filenames.push_back("decode_data_evb01_run12804_29_20240424T113044-aae9b396-e019-468e-9c02-f0900ce72f87.root");
    filenames.push_back("decode_data_evb01_run12804_29_20240424T113050-5b28f471-5125-4809-a63e-e6697bdcb8ef.root");
    filenames.push_back("decode_data_evb01_run12804_29_20240424T113056-078b8420-2473-470a-b08e-f7e2795f2eb9.root");
    filenames.push_back("decode_data_evb01_run12804_29_20240424T113102-47c95373-5297-4790-b002-b6001d139f66.root");
    filenames.push_back("decode_data_evb01_run12804_30_20240424T113634-3a9e0f20-35cb-439a-9655-86db6f09504f.root");
    filenames.push_back("decode_data_evb01_run12804_30_20240424T113638-44752e3a-b498-4fd1-9580-32fed4c72424.root");
    filenames.push_back("decode_data_evb01_run12804_30_20240424T113642-7c740ef4-ed94-4ba8-810b-8410a8b4c7b6.root");
    filenames.push_back("decode_data_evb01_run12804_30_20240424T113646-eced670b-5d06-4a10-85b4-260753331c3b.root");
    filenames.push_back("decode_data_evb01_run12804_31_20240424T114218-6df6b2a0-1974-406f-97e0-c476778a1e15.root");
    filenames.push_back("decode_data_evb01_run12804_31_20240424T114221-4d27e9c9-309a-448f-8c04-d389e5fec324.root");
    filenames.push_back("decode_data_evb01_run12804_31_20240424T114226-2fecc7cf-ff3d-48d1-9038-aa7ef4aea632.root");
    filenames.push_back("decode_data_evb01_run12804_31_20240424T114231-61e8d394-fcef-4a0c-a8cb-af6b4f33c0f4.root");
    filenames.push_back("decode_data_evb01_run12804_3_20240424T085314-850e27ed-4114-42f4-a6cd-eca72ff7ec63.root");
    filenames.push_back("decode_data_evb01_run12804_3_20240424T085317-fd29ed4e-b605-4ae7-b21c-4d9e70473678.root");
    filenames.push_back("decode_data_evb01_run12804_3_20240424T085322-29ae88bb-a5ce-4196-9aa6-c00554547025.root");
    filenames.push_back("decode_data_evb01_run12804_3_20240424T085325-cf9f7ad0-17a4-4c6d-b9fb-f4edb8ba0e4f.root");
    filenames.push_back("decode_data_evb01_run12804_32_20240424T114856-8a57fce6-a095-4630-ae9a-1e808d1d0ede.root");
    filenames.push_back("decode_data_evb01_run12804_32_20240424T114901-b2f04396-6dfa-4b24-baa1-412f621da6aa.root");
    filenames.push_back("decode_data_evb01_run12804_32_20240424T114908-deba0c9c-a5a3-4f02-b2e0-f9063c479680.root");
    filenames.push_back("decode_data_evb01_run12804_32_20240424T114914-17b8cdfd-8662-4072-910d-7e38bbac5326.root");
    filenames.push_back("decode_data_evb01_run12804_33_20240424T115512-6374c3cd-202d-4601-b881-d7bbab23ddab.root");
    filenames.push_back("decode_data_evb01_run12804_33_20240424T115516-c463d638-5879-4ab8-a550-16f210d6fd9d.root");
    filenames.push_back("decode_data_evb01_run12804_33_20240424T115519-4925a880-c93d-4008-8aa7-dd428abed759.root");
    filenames.push_back("decode_data_evb01_run12804_33_20240424T115523-9b009d13-9c4d-4b96-8273-85ff0d650b4a.root");
    filenames.push_back("decode_data_evb01_run12804_34_20240424T120059-7c80dde5-9447-43bb-8c5a-0e0c852e7d53.root");
    filenames.push_back("decode_data_evb01_run12804_34_20240424T120103-4e7ccefb-fc99-4db4-8e45-52320c32d571.root");
    filenames.push_back("decode_data_evb01_run12804_34_20240424T120109-62b93ef7-4aa1-49d5-9ce6-6b06613670ea.root");
    filenames.push_back("decode_data_evb01_run12804_34_20240424T120117-2fd6312d-554a-4920-891b-4715f1e4a246.root");
    filenames.push_back("decode_data_evb01_run12804_4_20240424T085906-31baab11-66f1-4b76-b740-2691db75659e.root");
    filenames.push_back("decode_data_evb01_run12804_4_20240424T085912-c142fb44-dc16-421c-9053-1452933ea591.root");
    filenames.push_back("decode_data_evb01_run12804_4_20240424T085918-2292b6d8-87f2-4a7a-84d9-9b57e732399a.root");
    filenames.push_back("decode_data_evb01_run12804_4_20240424T085922-411f26c4-6e98-49b5-8f6f-29a6a9faa37e.root");
    filenames.push_back("decode_data_evb01_run12804_5_20240424T090553-c23233e1-954f-4381-88b0-ac13d28418ae.root");
    filenames.push_back("decode_data_evb01_run12804_5_20240424T090600-10cb811d-a6ea-41f2-a364-3972633cf624.root");
    filenames.push_back("decode_data_evb01_run12804_5_20240424T090605-b006503e-7e11-4536-839b-33d97d323524.root");
    filenames.push_back("decode_data_evb01_run12804_5_20240424T090608-7491061c-5362-47ce-b3be-7027d61eb295.root");
    filenames.push_back("decode_data_evb01_run12804_6_20240424T091145-ba6d1bf5-60fe-4ef6-88d0-855d72a61270.root");
    filenames.push_back("decode_data_evb01_run12804_6_20240424T091150-13a040cb-5028-4cbd-b4ca-1c4b22a48608.root");
    filenames.push_back("decode_data_evb01_run12804_6_20240424T091154-86b1aefd-fd52-4f93-a5e3-67f8d3452ed0.root");
    filenames.push_back("decode_data_evb01_run12804_6_20240424T091158-1a542929-fb47-4bf5-91d4-5c2f4540f141.root");
    filenames.push_back("decode_data_evb01_run12804_7_20240424T091802-807d78db-9777-4491-a781-3d5ba91385ca.root");
    filenames.push_back("decode_data_evb01_run12804_7_20240424T091808-8518f4b1-96ad-4cfc-b623-1c2ca7011ac4.root");
    filenames.push_back("decode_data_evb01_run12804_7_20240424T091814-e4f92ca3-f473-42a4-816e-5d324baab805.root");
    filenames.push_back("decode_data_evb01_run12804_7_20240424T091818-515432ec-2620-4c0d-bc04-d33d47c860d4.root");
    filenames.push_back("decode_data_evb01_run12804_8_20240424T092412-a561a796-d80e-4373-bf85-c410b6e6c9e7.root");
    filenames.push_back("decode_data_evb01_run12804_8_20240424T092416-c4a732eb-114b-4580-ae4f-7a45986a151d.root");
    filenames.push_back("decode_data_evb01_run12804_8_20240424T092419-1baac8c3-026d-4500-9c12-52ae27c47bd0.root");
    filenames.push_back("decode_data_evb01_run12804_8_20240424T092422-14b6e964-97f3-4f45-84eb-ea3d45043a31.root");
    filenames.push_back("decode_data_evb01_run12804_9_20240424T092957-f8b665f8-fcf0-43cd-ac3a-472e480e939a.root");
    filenames.push_back("decode_data_evb01_run12804_9_20240424T093000-673c1596-84c8-49e7-b085-8e48aed3deca.root");
    filenames.push_back("decode_data_evb01_run12804_9_20240424T093005-d82b730b-0fc7-4429-b2cf-f077854e4337.root");
    filenames.push_back("decode_data_evb01_run12804_9_20240424T093009-bcb6040a-19ec-4c6b-9002-b0919ed8eca4.root");
    filenames.push_back("decode_data_evb02_run12804_10_20240424T093532-0f38b860-fbb3-48b7-9f1d-3ed731e39d9e.root");
    filenames.push_back("decode_data_evb02_run12804_10_20240424T093647-0427fb00-3c8b-463a-9c74-17323db19526.root");
    filenames.push_back("decode_data_evb02_run12804_10_20240424T093725-641c71bf-795f-4489-a05f-3597bc979a34.root");
    filenames.push_back("decode_data_evb02_run12804_10_20240424T093729-2db13a64-867c-47c8-afa7-df2927360ef0.root");
    filenames.push_back("decode_data_evb02_run12804_11_20240424T094130-852cece7-30f7-431d-9d0d-fd27d84d82f1.root");
    filenames.push_back("decode_data_evb02_run12804_11_20240424T094232-7b7c2fac-5bfb-4816-9ece-09f1278f3daa.root");
    filenames.push_back("decode_data_evb02_run12804_11_20240424T094314-9f580d14-b053-443e-a391-408f17e927b2.root");
    filenames.push_back("decode_data_evb02_run12804_11_20240424T094318-f415cb49-e449-44df-8dc7-c2ce6fc3a27d.root");
    filenames.push_back("decode_data_evb02_run12804_1_20240424T084118-27f36b22-58b7-4d70-8700-5b494976d007.root");
    filenames.push_back("decode_data_evb02_run12804_1_20240424T084142-57cd0723-022f-49f7-ba1f-571c39dbad75.root");
    filenames.push_back("decode_data_evb02_run12804_1_20240424T084212-ff1e93af-98ef-4aba-bcc6-cef652bd9101.root");
    filenames.push_back("decode_data_evb02_run12804_1_20240424T084218-5bf932e1-5a11-423f-baee-360b0c717a27.root");
    filenames.push_back("decode_data_evb02_run12804_12_20240424T094742-7186e1cd-9860-4244-bfb3-e1a9673a4b38.root");
    filenames.push_back("decode_data_evb02_run12804_12_20240424T094831-04563172-bebd-4cef-8967-cf2a5b2dad98.root");
    filenames.push_back("decode_data_evb02_run12804_12_20240424T094914-23d132cf-b088-48ec-84ab-6fc55138f162.root");
    filenames.push_back("decode_data_evb02_run12804_12_20240424T094918-735eec06-c6c8-48e5-a52c-843feb8fee77.root");
    filenames.push_back("decode_data_evb02_run12804_13_20240424T095323-9099314d-b06e-4b6b-b558-d7835f4b8c66.root");
    filenames.push_back("decode_data_evb02_run12804_13_20240424T095411-25c86005-ad0a-4c55-ac94-35e0292dab50.root");
    filenames.push_back("decode_data_evb02_run12804_13_20240424T095450-7406a4e9-e8ef-4d36-92e1-dc449bb8cc7e.root");
    filenames.push_back("decode_data_evb02_run12804_13_20240424T095454-067bd82f-7981-4703-bfab-59cb9dc94a53.root");
    filenames.push_back("decode_data_evb02_run12804_14_20240424T095907-b9e02d6f-4663-4a97-9c12-bef28f1814f6.root");
    filenames.push_back("decode_data_evb02_run12804_14_20240424T100003-8149e18b-6e86-49f3-8677-f06636d95e74.root");
    filenames.push_back("decode_data_evb02_run12804_14_20240424T100040-edb0bbba-7ffd-4149-a6bc-daf2db86c94b.root");
    filenames.push_back("decode_data_evb02_run12804_14_20240424T100044-209925d4-55aa-49e5-81bd-564b283f0746.root");
    filenames.push_back("decode_data_evb02_run12804_15_20240424T100442-2c0a7e70-e3d5-4519-ac5d-d1e0b51674cd.root");
    filenames.push_back("decode_data_evb02_run12804_15_20240424T100544-4944a0db-df6a-4787-9b48-7cd2e7f188bf.root");
    filenames.push_back("decode_data_evb02_run12804_15_20240424T100638-aff020e5-cde0-4daf-a683-700166575eab.root");
    filenames.push_back("decode_data_evb02_run12804_15_20240424T100644-56133bf2-815f-43cb-9b30-bd2c9472fccc.root");
    filenames.push_back("decode_data_evb02_run12804_16_20240424T101128-13c5a3b4-fe0c-4f9f-b8d1-a7a2eb32adce.root");
    filenames.push_back("decode_data_evb02_run12804_16_20240424T101230-b3ad8820-63b6-4f95-8c6f-21262d88faff.root");
    filenames.push_back("decode_data_evb02_run12804_16_20240424T101324-8b5551bd-924a-4244-a90c-d7d782f546ea.root");
    filenames.push_back("decode_data_evb02_run12804_16_20240424T101330-0ad55d96-5ef0-4b53-8c43-928291f97620.root");
    filenames.push_back("decode_data_evb02_run12804_17_20240424T101756-669bc0ec-6739-4acb-b72d-6d5519502f57.root");
    filenames.push_back("decode_data_evb02_run12804_17_20240424T101850-21eea39a-e829-42b4-9649-594f3862b79d.root");
    filenames.push_back("decode_data_evb02_run12804_17_20240424T101930-3251592e-bf46-420a-85d8-0b3c3f1d4be1.root");
    filenames.push_back("decode_data_evb02_run12804_17_20240424T101935-0934f4a2-d79a-4442-9838-c0267203f481.root");
    filenames.push_back("decode_data_evb02_run12804_18_20240424T102350-23e44941-c9f6-4c26-94be-76b54e669804.root");
    filenames.push_back("decode_data_evb02_run12804_18_20240424T102442-9f3c7d01-68ad-455f-827e-e66f27e47691.root");
    filenames.push_back("decode_data_evb02_run12804_18_20240424T102520-972960be-5341-4233-98f9-e17645a72465.root");
    filenames.push_back("decode_data_evb02_run12804_18_20240424T102523-b81ee7b4-f991-4b17-8280-824f7c44f95e.root");
    filenames.push_back("decode_data_evb02_run12804_19_20240424T103032-8eaedac4-8fb7-45fe-84c3-42453e7d4be4.root");
    filenames.push_back("decode_data_evb02_run12804_19_20240424T103141-c34668f0-ae67-4c64-8710-5b776b84bc0d.root");
    filenames.push_back("decode_data_evb02_run12804_19_20240424T103216-85cb1e5b-8327-43d3-bb4a-347c5ddef257.root");
    filenames.push_back("decode_data_evb02_run12804_19_20240424T103220-374a8db3-5334-433b-8ef5-286c46cab6ae.root");
    filenames.push_back("decode_data_evb02_run12804_20_20240424T103638-82e25022-2e28-4421-951a-63aead882d90.root");
    filenames.push_back("decode_data_evb02_run12804_20_20240424T103736-552f90da-f7d7-4dfa-b0c0-9ab6d56a0ac0.root");
    filenames.push_back("decode_data_evb02_run12804_20_20240424T103809-1b5a6d8f-2604-46ea-b93c-d31aecb14f05.root");
    filenames.push_back("decode_data_evb02_run12804_20_20240424T103813-3cd7e49c-7122-4c3e-900a-54d4ce7e7edf.root");
    filenames.push_back("decode_data_evb02_run12804_21_20240424T104208-1e2f36c1-aa89-4020-8b41-4fce62281522.root");
    filenames.push_back("decode_data_evb02_run12804_21_20240424T104303-bc53a768-edc4-4d0d-88ed-ebfa05fdc935.root");
    filenames.push_back("decode_data_evb02_run12804_21_20240424T104339-ff4626ef-f7b4-4ea7-ad12-ed7545930f1e.root");
    filenames.push_back("decode_data_evb02_run12804_21_20240424T104343-0bb48848-2e56-44fe-8233-a91a05a51881.root");
    filenames.push_back("decode_data_evb02_run12804_2_20240424T084610-9e566b9d-5a4c-4069-8813-613cf7c4c010.root");
    filenames.push_back("decode_data_evb02_run12804_2_20240424T084701-e5300039-55b0-4c65-bd25-d6233dcd0e80.root");
    filenames.push_back("decode_data_evb02_run12804_2_20240424T084755-ac201736-b086-42b4-b3ec-c6d12f0f0a05.root");
    filenames.push_back("decode_data_evb02_run12804_2_20240424T084801-088f3786-3a6b-4f5c-bb01-3b5d2fd06ffc.root");
    filenames.push_back("decode_data_evb02_run12804_22_20240424T104807-2a00e270-4061-483d-9146-e5937cde5b52.root");
    filenames.push_back("decode_data_evb02_run12804_22_20240424T104901-fc3378e5-de8d-4495-a3a8-f01e1b4de164.root");
    filenames.push_back("decode_data_evb02_run12804_22_20240424T104941-dca53578-ee43-4bc6-956a-a904f8785524.root");
    filenames.push_back("decode_data_evb02_run12804_22_20240424T104946-4bc19a89-6b2b-42f2-ae24-1b6072682220.root");
    filenames.push_back("decode_data_evb02_run12804_23_20240424T105410-9e37dca4-5079-4385-8f15-ba31c8062abe.root");
    filenames.push_back("decode_data_evb02_run12804_23_20240424T105507-91d5afa4-2095-4c14-9730-385c97ca61a6.root");
    filenames.push_back("decode_data_evb02_run12804_23_20240424T105550-2eb6b344-6edc-4ca8-abdd-c3ebe3aadd80.root");
    filenames.push_back("decode_data_evb02_run12804_23_20240424T105554-a5963951-9f09-4561-9e92-3b76ee794313.root");
    filenames.push_back("decode_data_evb02_run12804_24_20240424T110016-03783f61-8b74-4080-8fe6-6a8fdb01072f.root");
    filenames.push_back("decode_data_evb02_run12804_24_20240424T110112-cc77715d-2b01-4780-9afe-6b1b97c9e308.root");
    filenames.push_back("decode_data_evb02_run12804_24_20240424T110153-85b5a5f9-9f90-4b06-945e-8fcfa8086140.root");
    filenames.push_back("decode_data_evb02_run12804_24_20240424T110158-196320c7-bd86-4788-a1a5-a138783c5193.root");
    filenames.push_back("decode_data_evb02_run12804_25_20240424T110557-c69cc87b-98fa-4d70-8c32-4e2595425dbd.root");
    filenames.push_back("decode_data_evb02_run12804_25_20240424T110650-187d8da1-caac-458a-86b2-52c153ad32f7.root");
    filenames.push_back("decode_data_evb02_run12804_25_20240424T110726-0bbdea34-6a7f-4aa3-91b8-9b9df7a2fe75.root");
    filenames.push_back("decode_data_evb02_run12804_25_20240424T110729-076ccfcc-a810-4450-8179-edd522e64b4e.root");
    filenames.push_back("decode_data_evb02_run12804_26_20240424T111116-ef68e7bf-3ec9-4366-8303-efe7cc1a9a56.root");
    filenames.push_back("decode_data_evb02_run12804_26_20240424T111212-0879904b-cf5a-4c67-80b5-e3aaebfc5c09.root");
    filenames.push_back("decode_data_evb02_run12804_26_20240424T111257-4894896b-89cf-40ae-a64f-67c867fa5c2b.root");
    filenames.push_back("decode_data_evb02_run12804_26_20240424T111300-55276cd1-d46f-4e0f-8ef7-8b0d93deb6ef.root");
    filenames.push_back("decode_data_evb02_run12804_27_20240424T111733-2911dfb5-0d1a-4de5-be53-e5fdbb4d3cf0.root");
    filenames.push_back("decode_data_evb02_run12804_27_20240424T111844-70a5bee5-44d5-411f-9dd1-f202ecda66eb.root");
    filenames.push_back("decode_data_evb02_run12804_27_20240424T111918-97bae730-065c-4176-8cdb-fccfa2a69240.root");
    filenames.push_back("decode_data_evb02_run12804_27_20240424T111922-cd2948c7-6b9d-4577-9044-9085fbf168e7.root");
    filenames.push_back("decode_data_evb02_run12804_28_20240424T112334-5e7758ef-fc45-4440-a8e2-6a77ca9ab8a5.root");
    filenames.push_back("decode_data_evb02_run12804_28_20240424T112428-fdad86cb-fd0c-4d06-91b7-2ef5d77e895e.root");
    filenames.push_back("decode_data_evb02_run12804_28_20240424T112508-37d5464a-e36f-4a86-b09d-216c3fc29b87.root");
    filenames.push_back("decode_data_evb02_run12804_28_20240424T112514-55d1842f-6076-4a78-99ce-24c8cb2c6240.root");
    filenames.push_back("decode_data_evb02_run12804_29_20240424T112932-3824d0d5-c847-45c5-b6bd-bf7951966f8c.root");
    filenames.push_back("decode_data_evb02_run12804_29_20240424T113046-16d0bf53-1b71-4f3a-833f-3f438378c0f8.root");
    filenames.push_back("decode_data_evb02_run12804_29_20240424T113130-3a555b51-3722-4fa8-91fe-44f5986e1bb3.root");
    filenames.push_back("decode_data_evb02_run12804_29_20240424T113134-1378161b-fba7-4638-bf68-70526900e35f.root");
    filenames.push_back("decode_data_evb02_run12804_30_20240424T113545-be2a2cf4-7873-4413-b76c-a0031a3f395d.root");
    filenames.push_back("decode_data_evb02_run12804_30_20240424T113635-58081720-a291-4c53-ad75-465a6dddbac4.root");
    filenames.push_back("decode_data_evb02_run12804_30_20240424T113711-26d4d534-71fd-4617-a58d-ae720fdffdaf.root");
    filenames.push_back("decode_data_evb02_run12804_30_20240424T113715-9a589c59-9830-4dca-8009-3864f0344b81.root");
    filenames.push_back("decode_data_evb02_run12804_31_20240424T114120-57b00fe5-b50e-4fd4-b6d9-a095aee95163.root");
    filenames.push_back("decode_data_evb02_run12804_31_20240424T114219-6e3f70be-d7d2-48d0-b22b-29e1f7f8e417.root");
    filenames.push_back("decode_data_evb02_run12804_31_20240424T114258-5c2cc1f6-75c6-4967-b60a-83f799972676.root");
    filenames.push_back("decode_data_evb02_run12804_31_20240424T114302-f13be282-30b6-49d5-8297-d883783321fa.root");
    filenames.push_back("decode_data_evb02_run12804_3_20240424T085216-7a6eaf1b-4dea-4f0f-8115-85acc8997f46.root");
    filenames.push_back("decode_data_evb02_run12804_3_20240424T085315-80351120-aade-4f78-926b-1b1fcd2ab9a4.root");
    filenames.push_back("decode_data_evb02_run12804_3_20240424T085353-46adb3f7-390f-4547-a646-07cf6c815ed1.root");
    filenames.push_back("decode_data_evb02_run12804_3_20240424T085356-e69a08f5-9b2c-4a39-9709-b211c6b8306d.root");
    filenames.push_back("decode_data_evb02_run12804_32_20240424T114756-49cc7a57-1e8d-47db-acad-459f5a5fba45.root");
    filenames.push_back("decode_data_evb02_run12804_32_20240424T114858-9448fb7d-8691-4078-9881-ef8619f3d8c9.root");
    filenames.push_back("decode_data_evb02_run12804_32_20240424T114948-d54a1551-e01f-474d-bdd8-c13a81956c1e.root");
    filenames.push_back("decode_data_evb02_run12804_32_20240424T114953-fc58a2ee-feba-4211-b343-f7394874033a.root");
    filenames.push_back("decode_data_evb02_run12804_33_20240424T115414-4211a198-85f9-4f6d-a1be-506d27782000.root");
    filenames.push_back("decode_data_evb02_run12804_33_20240424T115513-e85d2f9b-7fd3-450f-82e0-fe8b08023792.root");
    filenames.push_back("decode_data_evb02_run12804_33_20240424T115549-68701a13-e3f3-4982-8575-5d8ed52f8b31.root");
    filenames.push_back("decode_data_evb02_run12804_33_20240424T115552-cc242a72-67e4-447f-bb4f-2a8ff2e3adcf.root");
    filenames.push_back("decode_data_evb02_run12804_34_20240424T120006-da226daf-cd03-4efc-bc87-4c6713b3564b.root");
    filenames.push_back("decode_data_evb02_run12804_34_20240424T120101-0f27610f-41bb-4e4e-af65-e3fe9a35cd56.root");
    filenames.push_back("decode_data_evb02_run12804_4_20240424T085806-02ca6b16-65d4-4a42-a01f-1122166fb72f.root");
    filenames.push_back("decode_data_evb02_run12804_4_20240424T085908-0f8769fe-ef91-4149-aa16-a75a6a88d7dc.root");
    filenames.push_back("decode_data_evb02_run12804_4_20240424T085956-09f8fc0e-0a87-469a-85b8-72e692f6ee9e.root");
    filenames.push_back("decode_data_evb02_run12804_4_20240424T090002-15123bd6-9f76-4ce6-b607-93f7ca3ed78c.root");
    filenames.push_back("decode_data_evb02_run12804_5_20240424T090457-f5ad053a-4c9d-40b1-985a-ab1ef6ab887e.root");
    filenames.push_back("decode_data_evb02_run12804_5_20240424T090556-89bb15fa-fa58-4c33-bb8a-a731dc1e4e5f.root");
    filenames.push_back("decode_data_evb02_run12804_5_20240424T090634-f48855dd-4f9d-4552-b007-8a4dbfe31e4e.root");
    filenames.push_back("decode_data_evb02_run12804_5_20240424T090638-0005ce59-a2bd-4b6a-8dc4-28edec8c0ab0.root");
    filenames.push_back("decode_data_evb02_run12804_6_20240424T091038-8a77631c-ff0f-40dc-8ab6-d307554bd506.root");
    filenames.push_back("decode_data_evb02_run12804_6_20240424T091146-571860c1-2169-4a68-aea1-4c4407912525.root");
    filenames.push_back("decode_data_evb02_run12804_6_20240424T091221-747ef574-7553-4149-a9a7-4c73174a8670.root");
    filenames.push_back("decode_data_evb02_run12804_6_20240424T091226-43d61e10-c099-4140-bc30-45135a51806d.root");
    filenames.push_back("decode_data_evb02_run12804_7_20240424T091648-cbbe174a-fd22-4729-999c-f4075343717f.root");
    filenames.push_back("decode_data_evb02_run12804_7_20240424T091804-298427e3-8781-4999-bb39-cdb522fccc89.root");
    filenames.push_back("decode_data_evb02_run12804_7_20240424T091846-61b86e54-e482-4ec9-9d1e-03ee522b3461.root");
    filenames.push_back("decode_data_evb02_run12804_7_20240424T091852-5bb545fc-f4de-4293-b9f6-67df145bb560.root");
    filenames.push_back("decode_data_evb02_run12804_8_20240424T092315-73ccc0fb-31d4-4c47-ba12-00cfbd219282.root");
    filenames.push_back("decode_data_evb02_run12804_8_20240424T092413-21f60aea-e77c-4321-937b-7bf8a94fe636.root");
    filenames.push_back("decode_data_evb02_run12804_8_20240424T092448-3243b120-ac81-470d-831a-2ed4372d0bd3.root");
    filenames.push_back("decode_data_evb02_run12804_8_20240424T092452-6cd1182b-e7b1-4dab-8e10-266621965a40.root");
    filenames.push_back("decode_data_evb02_run12804_9_20240424T092905-640ab114-1147-47d7-8d29-55a0750b2ca4.root");
    filenames.push_back("decode_data_evb02_run12804_9_20240424T092958-c46294e6-aa75-4f1e-ae1f-c60326b80141.root");
    filenames.push_back("decode_data_evb02_run12804_9_20240424T093032-b6131737-edf4-4046-9d80-54388cefbee8.root");
    filenames.push_back("decode_data_evb02_run12804_9_20240424T093037-763ba174-5ae5-4e15-bd42-5926947d14cb.root");
    filenames.push_back("decode_data_evb03_run12803_2_20240424T054955-72ac4d28-5ce1-4cdb-99c5-eed4622d5df1.root");
    filenames.push_back("decode_data_evb03_run12804_10_20240424T093644-fe69672f-9463-4177-8430-6fa6abb36f39.root");
    filenames.push_back("decode_data_evb03_run12804_10_20240424T093649-e6b28db8-4bdd-42ed-a1de-1fa640b3e5a8.root");
    filenames.push_back("decode_data_evb03_run12804_10_20240424T093657-e5165730-1959-4264-8aa6-dc10c3334831.root");
    filenames.push_back("decode_data_evb03_run12804_10_20240424T093709-032d4cba-5bae-4e85-ae78-0a077f02bb5b.root");
    filenames.push_back("decode_data_evb03_run12804_11_20240424T094228-b8b210d1-6b43-413e-b18a-3d011cee351c.root");
    filenames.push_back("decode_data_evb03_run12804_11_20240424T094234-e9fa635e-4a44-444c-a1e3-8e3a2c2347c2.root");
    filenames.push_back("decode_data_evb03_run12804_11_20240424T094246-f7aaada2-a44c-4dc8-b274-446589f17326.root");
    filenames.push_back("decode_data_evb03_run12804_11_20240424T094301-b81b5dff-bc05-49aa-9769-2dbfb3b9cf61.root");
    filenames.push_back("decode_data_evb03_run12804_1_20240424T084120-23bc98bf-679d-435a-b97d-b5c6cb281ba4.root");
    filenames.push_back("decode_data_evb03_run12804_1_20240424T084126-a238433f-2388-4184-ad24-8ce2f78cb9bc.root");
    filenames.push_back("decode_data_evb03_run12804_1_20240424T084132-c55cf3b6-b2d3-41d8-9d7e-412cf68dcbd5.root");
    filenames.push_back("decode_data_evb03_run12804_1_20240424T084150-c3eb012c-d727-4ccb-b985-8ccdd1e92320.root");
    filenames.push_back("decode_data_evb03_run12804_12_20240424T094829-9152c0de-f6af-41be-8fc7-583b44d40328.root");
    filenames.push_back("decode_data_evb03_run12804_12_20240424T094833-f692462c-c1c6-4a27-9b83-987bbd6de07e.root");
    filenames.push_back("decode_data_evb03_run12804_12_20240424T094844-d17a3f66-432a-4f80-b04c-66ef84e6fdce.root");
    filenames.push_back("decode_data_evb03_run12804_12_20240424T094858-9b1c6c1e-04a5-47d0-bdda-72d811b52eef.root");
    filenames.push_back("decode_data_evb03_run12804_13_20240424T095409-bdb5fa53-917f-456a-9e35-7900cfb1df0a.root");
    filenames.push_back("decode_data_evb03_run12804_13_20240424T095413-633db924-c61c-4e3e-b94d-649599b0e364.root");
    filenames.push_back("decode_data_evb03_run12804_13_20240424T095422-ecff64c0-5159-4ad0-b896-a48cd7955792.root");
    filenames.push_back("decode_data_evb03_run12804_13_20240424T095434-7401b644-ae2e-4eea-a419-64a55adc4a14.root");
    filenames.push_back("decode_data_evb03_run12804_14_20240424T100001-5d8894e4-0adb-471f-8acf-f04950c08591.root");
    filenames.push_back("decode_data_evb03_run12804_14_20240424T100004-f3b818f4-fd40-4f73-8b7c-b2f241540056.root");
    filenames.push_back("decode_data_evb03_run12804_14_20240424T100011-cf2497d6-c4f7-49bb-ad68-9d5c9c355c53.root");
    filenames.push_back("decode_data_evb03_run12804_14_20240424T100025-7e9e10b1-b5da-4037-a32f-483d3522fe30.root");
    filenames.push_back("decode_data_evb03_run12804_15_20240424T100540-31800b0c-159f-4294-a628-b9a7b411e249.root");
    filenames.push_back("decode_data_evb03_run12804_15_20240424T100546-2a0169a6-4b7a-4af5-9ffe-bcd8dac420dc.root");
    filenames.push_back("decode_data_evb03_run12804_15_20240424T100558-fa4e58ab-0d04-4158-a320-6d94337950f4.root");
    filenames.push_back("decode_data_evb03_run12804_15_20240424T100616-8db66cae-6bea-460b-80d1-e283077dcd31.root");
    filenames.push_back("decode_data_evb03_run12804_16_20240424T101226-f99c1e0c-b611-40ef-823b-2849411e83c5.root");
    filenames.push_back("decode_data_evb03_run12804_16_20240424T101232-01f4d332-5840-4bcd-b95d-5a76a1a5b299.root");
    filenames.push_back("decode_data_evb03_run12804_16_20240424T101244-4e2fa15d-1439-47cd-b995-3b07d4ad1b5f.root");
    filenames.push_back("decode_data_evb03_run12804_16_20240424T101302-af5806de-ffdd-4f9a-b74e-c878ecb473ab.root");
    filenames.push_back("decode_data_evb03_run12804_17_20240424T101846-e4ff792d-71ec-481a-833c-739336577f6e.root");
    filenames.push_back("decode_data_evb03_run12804_17_20240424T101851-c58fdcc5-089e-4c25-8124-be4f85820664.root");
    filenames.push_back("decode_data_evb03_run12804_17_20240424T101901-23fcd33d-8049-482e-9835-b71752f0555e.root");
    filenames.push_back("decode_data_evb03_run12804_17_20240424T101914-0954d385-dbee-4fe5-ad58-71f9ef6bffce.root");
    filenames.push_back("decode_data_evb03_run12804_18_20240424T102440-0d791905-2f0b-41d4-8ba0-23528c822c33.root");
    filenames.push_back("decode_data_evb03_run12804_18_20240424T102443-e7fbdb27-9c67-4861-a8c9-9969e773c944.root");
    filenames.push_back("decode_data_evb03_run12804_18_20240424T102451-9c6ee4f7-20b9-43ac-a292-39f459456ffa.root");
    filenames.push_back("decode_data_evb03_run12804_18_20240424T102505-c6480907-a709-4714-9086-d02817c20e5f.root");
    filenames.push_back("decode_data_evb03_run12804_19_20240424T103139-5741ad42-a677-4dfe-8e4b-1d5377c47b66.root");
    filenames.push_back("decode_data_evb03_run12804_19_20240424T103143-bf829b45-7bd3-4a36-a420-785d0e1a7c3e.root");
    filenames.push_back("decode_data_evb03_run12804_19_20240424T103151-7000f0e4-ecd4-4cd3-a0ed-e793d990f648.root");
    filenames.push_back("decode_data_evb03_run12804_19_20240424T103201-99d04e3c-e9cc-463a-8602-a61a883188a1.root");
    filenames.push_back("decode_data_evb03_run12804_20_20240424T103733-2861002c-47f3-40e5-a757-d5dc49ef9a0a.root");
    filenames.push_back("decode_data_evb03_run12804_20_20240424T103737-1a1db269-239a-444c-a3a3-64b811cb05c3.root");
    filenames.push_back("decode_data_evb03_run12804_20_20240424T103745-1dd167be-7a38-459f-b97e-cbd073cac42a.root");
    filenames.push_back("decode_data_evb03_run12804_20_20240424T103756-977b2d8e-f614-4376-9de2-663020b4cf4b.root");
    filenames.push_back("decode_data_evb03_run12804_21_20240424T104300-1b3a5797-846a-4088-8b8b-dfe3fd338baa.root");
    filenames.push_back("decode_data_evb03_run12804_21_20240424T104304-26f1a799-ecbe-4307-9de1-e98731958211.root");
    filenames.push_back("decode_data_evb03_run12804_21_20240424T104311-19973508-8531-44b0-b749-1348f8d2f876.root");
    filenames.push_back("decode_data_evb03_run12804_21_20240424T104324-e206311c-7a94-4ed8-b566-7ccb197e5eb4.root");
    filenames.push_back("decode_data_evb03_run12804_2_20240424T084657-045825f6-6164-4e63-bf4e-51a0c00635fd.root");
    filenames.push_back("decode_data_evb03_run12804_2_20240424T084703-182b1c65-a003-4ac0-8066-2c6f244b42c6.root");
    filenames.push_back("decode_data_evb03_run12804_2_20240424T084715-ea04017c-2a60-4113-8591-84a6d6290817.root");
    filenames.push_back("decode_data_evb03_run12804_2_20240424T084733-2fee7c43-5901-4de4-adb1-2de2a0fb13bb.root");
    filenames.push_back("decode_data_evb03_run12804_22_20240424T104858-a3909caf-d398-4f0f-a810-4a55513d8ef3.root");
    filenames.push_back("decode_data_evb03_run12804_22_20240424T104902-cc25f9d6-aee5-450c-9ca3-e296ff196fb7.root");
    filenames.push_back("decode_data_evb03_run12804_22_20240424T104911-b92d65e0-94e2-43e0-9667-71f153157122.root");
    filenames.push_back("decode_data_evb03_run12804_22_20240424T104923-5b3b038d-80ec-48b0-9358-4425cb0c5e6e.root");
    filenames.push_back("decode_data_evb03_run12804_23_20240424T105504-2b405f9c-ea21-4cc2-9d8d-c95915280fa1.root");
    filenames.push_back("decode_data_evb03_run12804_23_20240424T105509-4ccd6a0e-9e00-4e84-ae45-3cda0d834e2f.root");
    filenames.push_back("decode_data_evb03_run12804_23_20240424T105517-776946bf-465c-4fd1-b725-ab2f0415cf3b.root");
    filenames.push_back("decode_data_evb03_run12804_23_20240424T105533-cf406763-d8f2-4180-b40e-9d3767b60c92.root");
    filenames.push_back("decode_data_evb03_run12804_24_20240424T110108-92785403-cf77-4493-9246-559c32ba3d9e.root");
    filenames.push_back("decode_data_evb03_run12804_24_20240424T110114-20cea54d-d273-4379-a3ec-f7337dc4e95d.root");
    filenames.push_back("decode_data_evb03_run12804_24_20240424T110126-2ce907c5-f93c-4b58-ac1d-689bb7883533.root");
    filenames.push_back("decode_data_evb03_run12804_24_20240424T110138-8f05a577-abf7-434d-a0f7-8a2662ebf383.root");
    filenames.push_back("decode_data_evb03_run12804_25_20240424T110648-14546167-b48b-4dc8-a1ab-3eb668e7afec.root");
    filenames.push_back("decode_data_evb03_run12804_25_20240424T110651-44201de6-366f-4e2c-aaf9-5cc3d685963a.root");
    filenames.push_back("decode_data_evb03_run12804_25_20240424T110658-470e89c4-b3b2-491a-be9c-bc6f445cce3c.root");
    filenames.push_back("decode_data_evb03_run12804_25_20240424T110711-754759ef-bf1f-49f8-872b-3c2c9d391794.root");
    filenames.push_back("decode_data_evb03_run12804_26_20240424T111208-157b08b5-1447-46fe-877e-c3e5f66d49c0.root");
    filenames.push_back("decode_data_evb03_run12804_26_20240424T111214-979c6284-42ec-439e-a900-838e28e98024.root");
    filenames.push_back("decode_data_evb03_run12804_26_20240424T111226-ae0bd701-41c5-4190-bab6-387bfa99011e.root");
    filenames.push_back("decode_data_evb03_run12804_26_20240424T111242-dab0fc4d-5983-4bff-90f7-bb572493a44c.root");
    filenames.push_back("decode_data_evb03_run12804_27_20240424T111841-24022f38-e5bc-4e7e-9ddb-9b4c4b43d1ca.root");
    filenames.push_back("decode_data_evb03_run12804_27_20240424T111845-c7887bab-35d8-499c-9cd4-27fc5088c24c.root");
    filenames.push_back("decode_data_evb03_run12804_27_20240424T111852-4006a994-e5f2-4f9e-ba12-6f2e1f33b263.root");
    filenames.push_back("decode_data_evb03_run12804_27_20240424T111903-18ccdd94-2d1a-46e6-a4e8-a1a68d9bc102.root");
    filenames.push_back("decode_data_evb03_run12804_28_20240424T112424-3cb9706d-7d34-4f85-9af1-a42b180656f6.root");
    filenames.push_back("decode_data_evb03_run12804_28_20240424T112429-78e455bd-c742-4c5f-824c-83f29aeca79f.root");
    filenames.push_back("decode_data_evb03_run12804_28_20240424T112438-99bcaff8-dbdb-451d-b094-f95f97f001c2.root");
    filenames.push_back("decode_data_evb03_run12804_28_20240424T112449-d632e95d-8fbb-4a1b-8f85-964e438a902d.root");
    filenames.push_back("decode_data_evb03_run12804_29_20240424T113042-6b244558-8702-48e0-aa2c-f42edecf2234.root");
    filenames.push_back("decode_data_evb03_run12804_29_20240424T113048-fabf1858-7278-414e-819c-4e9e7f2d81d4.root");
    filenames.push_back("decode_data_evb03_run12804_29_20240424T113100-99e6afda-de2c-458b-95a5-993a30fae548.root");
    filenames.push_back("decode_data_evb03_run12804_29_20240424T113116-04fd92bb-f59f-4fc1-9d55-f747fb6a1d69.root");
    filenames.push_back("decode_data_evb03_run12804_30_20240424T113633-9f07ea4e-e440-46dc-b512-c1cce4d21704.root");
    filenames.push_back("decode_data_evb03_run12804_30_20240424T113637-52f91f2e-c801-438f-b48d-e536c9807940.root");
    filenames.push_back("decode_data_evb03_run12804_30_20240424T113644-46139ad1-0273-4fcb-bb3d-d985579ec270.root");
    filenames.push_back("decode_data_evb03_run12804_30_20240424T113656-82a50b0f-dfac-4037-8378-489a6a39ae51.root");
    filenames.push_back("decode_data_evb03_run12804_31_20240424T114216-023a036c-728d-462e-a944-1b07c5904f34.root");
    filenames.push_back("decode_data_evb03_run12804_31_20240424T114220-ffab2975-44be-41db-9555-a1314e78ce03.root");
    filenames.push_back("decode_data_evb03_run12804_31_20240424T114230-ffa560bb-c213-4205-a2bf-e0e4f0d77c7b.root");
    filenames.push_back("decode_data_evb03_run12804_31_20240424T114245-4cc06986-84c0-4a82-a973-793e47ca53e4.root");
    filenames.push_back("decode_data_evb03_run12804_3_20240424T085312-ecec8330-94b6-489b-895f-81b5f528cecd.root");
    filenames.push_back("decode_data_evb03_run12804_3_20240424T085316-d461098d-aeba-4d21-9272-5f4fa98be23a.root");
    filenames.push_back("decode_data_evb03_run12804_3_20240424T085324-9d3d2a21-3bd6-43d3-9589-695baf5b0694.root");
    filenames.push_back("decode_data_evb03_run12804_3_20240424T085336-a86afee1-f3f8-417b-81ae-466184b34233.root");
    filenames.push_back("decode_data_evb03_run12804_32_20240424T114854-99dfe23e-bad6-4360-940c-066a32d617ac.root");
    filenames.push_back("decode_data_evb03_run12804_32_20240424T114900-d1ba4a0e-83f7-4f63-a79f-b1d9fc1753b3.root");
    filenames.push_back("decode_data_evb03_run12804_32_20240424T114912-69166b38-3b35-42db-ab4c-a503b7b9c05b.root");
    filenames.push_back("decode_data_evb03_run12804_32_20240424T114928-afe9cc09-225d-4602-bbc9-8d48b824f229.root");
    filenames.push_back("decode_data_evb03_run12804_33_20240424T115511-5b93e001-e8ca-4a68-9dce-7dd2757cbca1.root");
    filenames.push_back("decode_data_evb03_run12804_33_20240424T115515-12ea426c-4d08-407d-9e11-c765b9b1d9a2.root");
    filenames.push_back("decode_data_evb03_run12804_33_20240424T115522-ff5de22d-c732-46fd-b36c-516d1fc65878.root");
    filenames.push_back("decode_data_evb03_run12804_33_20240424T115534-b3c43633-f6ae-4984-9dee-f9a1156ff600.root");
    filenames.push_back("decode_data_evb03_run12804_34_20240424T120057-dbcf4eb3-8338-4ba6-922c-602a51ebfd2a.root");
    filenames.push_back("decode_data_evb03_run12804_34_20240424T120102-bd9f33ab-fcc7-4280-91f2-9fba014cff67.root");
    filenames.push_back("decode_data_evb03_run12804_34_20240424T120112-33f73e86-8bc5-461d-8af4-bc2ff70aa6a5.root");
    filenames.push_back("decode_data_evb03_run12804_4_20240424T085904-7e3eb102-128c-4e2c-b38e-7e8f00cd7f4f.root");
    filenames.push_back("decode_data_evb03_run12804_4_20240424T085910-844856ef-988d-4101-b566-e4d4477c4e64.root");
    filenames.push_back("decode_data_evb03_run12804_4_20240424T085921-42b088e6-d040-4c7e-a1ed-de27152cd71e.root");
    filenames.push_back("decode_data_evb03_run12804_4_20240424T085935-9c2eaca3-fd2b-4e1d-ab99-a992526bd974.root");
    filenames.push_back("decode_data_evb03_run12804_5_20240424T090552-377b1d3f-0c09-4fea-a8f1-38093e8c6c91.root");
    filenames.push_back("decode_data_evb03_run12804_5_20240424T090558-eddaace5-ad41-4f2a-b107-9c0983a152ed.root");
    filenames.push_back("decode_data_evb03_run12804_5_20240424T090607-57cf3186-2bbf-4281-9113-0f8002ed2472.root");
    filenames.push_back("decode_data_evb03_run12804_5_20240424T090619-70ece047-bea7-4a39-93a3-39f3426a9be5.root");
    filenames.push_back("decode_data_evb03_run12804_6_20240424T091144-748f3197-0603-434c-a051-6f918bcd4f4c.root");
    filenames.push_back("decode_data_evb03_run12804_6_20240424T091148-499fdbc7-44b8-43bc-9c26-c103b22c3753.root");
    filenames.push_back("decode_data_evb03_run12804_6_20240424T091156-e4a4da80-821c-480d-96f1-85ed15126c94.root");
    filenames.push_back("decode_data_evb03_run12804_6_20240424T091208-918b27c7-b6b1-4bc9-a559-5f431eb7adc7.root");
    filenames.push_back("decode_data_evb03_run12804_7_20240424T091800-2f1d8a8a-89f0-46b1-be4a-1c1b2ca28e54.root");
    filenames.push_back("decode_data_evb03_run12804_7_20240424T091806-5cd4c093-eb09-4a4f-97c7-5e43e87528d0.root");
    filenames.push_back("decode_data_evb03_run12804_7_20240424T091816-dc6d3461-64df-4c0c-8348-456364427d55.root");
    filenames.push_back("decode_data_evb03_run12804_7_20240424T091831-a204f6b7-c4f8-493c-8887-f7d09f63465d.root");
    filenames.push_back("decode_data_evb03_run12804_8_20240424T092411-96a8610d-1755-443e-bae2-6e670f4f1133.root");
    filenames.push_back("decode_data_evb03_run12804_8_20240424T092414-c6012df9-2d33-4c22-9e9a-47dbea3228ac.root");
    filenames.push_back("decode_data_evb03_run12804_8_20240424T092421-29df4c24-c6b2-4937-b69e-c92eee57fa0e.root");
    filenames.push_back("decode_data_evb03_run12804_8_20240424T092433-b2c6b1e2-8246-4256-8ca4-279aca96338a.root");
    filenames.push_back("decode_data_evb03_run12804_9_20240424T092955-c06e3fe5-3f59-4e1c-b1ef-245c18d41e6c.root");
    filenames.push_back("decode_data_evb03_run12804_9_20240424T092959-8586d0fc-5a79-4638-9ec7-d713814ce64a.root");
    filenames.push_back("decode_data_evb03_run12804_9_20240424T093008-9948e480-e492-44ee-b01d-c4703d75a1ff.root");
    filenames.push_back("decode_data_evb03_run12804_9_20240424T093019-8ffa79c4-5ea4-4239-aaf3-d50ebcb7e081.root");
  
  for (gallery::Event ev(filenames); !ev.atEnd(); ev.next()) {
    auto const& rdtimestamps = *ev.getValidHandle<vector<raw::RDTimeStamp>>(rdts_tag);
    if (!rdtimestamps.empty())
      {
	const size_t nrdts = rdtimestamps.size();
	auto const& evaux = ev.eventAuxiliary();
	int runno = evaux.run();
	int subrunno = evaux.subRun();
	int eventno = evaux.event();

	uint64_t tsmin = rdtimestamps.at(0).GetTimeStamp();
	uint64_t tsmax = tsmin;
	
	for (const auto & rdts : rdtimestamps)
	  {
	    uint64_t ts = rdts.GetTimeStamp();
	    if (ts < tsmin) tsmin = ts;
	    if (ts > tsmax) tsmax = ts;
	  }
	//std::cout << eventno << " " << tsmax - tsmin << std::endl;
	tsdiff->Fill(eventno, tsmax - tsmin);
      }
  }
  tsdiff->Draw("hist");
  mycanvas->Print("tsdiff_vs_event_run12804.png");
}
