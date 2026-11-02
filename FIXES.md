# Fixes on this branch

One row per port I changed on this branch (`origin/main..hybrid-fixes`). Columns: the exe address of the port, its name from the plan, the defect class, the commit(s) that changed it, and how the change was checked.

How the changes were checked:

- **spec corrected, n=1000 both seeds**: the pilot spec was fixed together with the port (callee stubs that check and clobber ECX/EDX and pop what the original callee pops), the old port fails it and the new one passes at n=1000 on seeds 1 and 2. **pilot n=1000 both seeds**: the existing spec was re-run on the new port without changes. **pilot n/a**: the spec needs a data file that is not in the repo.
- **shadow replay exact**: the original function and the port were replayed in Unicorn on CPU and memory state captured from a real game run (a process snapshot at the function entry), and memory writes, calls, stack balance, callee-saved registers and the returned state matched.
- **in-game acceptance**: the port was enabled in the real exe (a proxy DLL patches a jump to the linked ports image) and a scripted route ran without a crash: menus, a new game into C01A, and the hub map into C02B. This only shows the route survives, not that every branch is right.
- **draft, not verified in-game**: commits 1163617, 82b0634, fab35c0, c6ebf84 and 429df5f. The image built with them never got the scripted route into C02B, so one of them may be wrong. Please treat these rows as drafts.
- **not verified**: the source changed but the machine code or the checks above did not cover it.

Sysobj slot pop counts behind most "slot arity / pending pushes" rows: slot 0x114 pops 4 arguments (ret 0x10), slots 0x4c and 0x58 pop 1 (ret 4), and the slots that usually follow them (0x128, 0x12c, 0x130) take 3. Words pushed for the first call beyond what it pops stay on the stack and become the trailing arguments of the next call.

| address | name | defect class | commit | verification |
|---|---|---|---|---|
| 0x41e080 | read file into parser (gap band parked) cdecl | calling convention / missing this | ec21164 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x41f3a0 | CRT helper 0x41f3a0 (unknown) thiscall | calling convention / missing this | ae0dc1f | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x41fa40 | ZSysMemGC::SubLink (unknown) thiscall | calling convention / missing this | ae0dc1f | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x4234f0 | GUESS serialize engine and process clock samples | other (missing logic) | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x425d30 | GUESS lifted 0x425d30 | slot arity / pending pushes | 2fb7d9d | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x4260a0 | GUESS lifted 0x4260a0 | slot arity / pending pushes | ac2c339 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x42abbd | GUESS call and clamp error | slot arity / pending pushes | faec454 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x42ac56 | wrap42ac56 (GUESS) cdecl | slot arity / pending pushes | faec454 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x438910 | GUESS drain_iterator_unlink | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; shadow replay exact; in-game acceptance |
| 0x438c10 | forwardVt10 (unknown) thiscall | jmp forwarder as call | faec454 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x438cc0 | ZInputActions::GetActionMap(const char*) | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x439020 | ZInputActions::GetButtonName (unknown) stdcall | calling convention / missing this | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x439760 | ZInputAction::MakeActionExclusiveOwnerOfNodes(bool) (vtable-map name)  | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x43a800 | ZInputActions::RemoveActionMaps | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x43a900 | GUESS lifted 0x43a900 | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; shadow replay exact; in-game acceptance |
| 0x4402a0 | GUESS hand 0x4402a0 | iterator local too small | ac2c339 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x444530 | GUESS hand 0x444530 | iterator local too small | ac2c339 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x449920 | ZGateLightSpotMaster::SetMultiplier | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x44a160 | ZLIST::CheckPointInside | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x453390 | GUESS hand 0x453390 | iterator local too small | ac2c339 | spec corrected, n=1000 both seeds |
| 0x454f20 | ZMaterialDescGroup::GetMaterialDescriptor | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x45bf40 | GUESS log and update | slot arity / pending pushes | 429df5f | draft, not verified in-game |
| 0x45c6a0 | ZGEOM::ActivateEvents() | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x45d1f0 | refreshLoop (GUESS) | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x45d3a0 | GUESS lifted 0x45d3a0 | calling convention / missing this | ae0dc1f | not verified |
| 0x4627d0 | GUESS lifted 0x4627d0 | calling convention / missing this | ec21164 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x465850 | compare_const_bool | u32 return (bool upper bits) | 858debe | pilot n=1000 both seeds; in-game acceptance |
| 0x465fd0 | GUESS initialize_and_dispatch_engine_resource | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x4668d0 | GUESS lifted 0x4668d0 | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x4670b0 | ZIKLNKOBJ PlaySoundFootStep | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x467260 | GUESS replace_effect_handle | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x46a4f0 | ZItem::~ZItem() | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x46bca0 | ZItem::ClassInit2 (unknown) thiscall | calling convention / missing this | ae0dc1f | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x46cc20 | ZItemTemplateWeapon::CopyData (unknown) thiscall | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x46eef0 | copy3Check (unknown) thiscall | u32 return (bool upper bits) | 858debe | pilot n=1000 both seeds; in-game acceptance |
| 0x470920 | GUESS send a text when allowed | slot arity / pending pushes | 82b0634 | draft, not verified in-game |
| 0x470a00 | GUESS conditionally bind a script handler to an actor | slot arity / pending pushes | 82b0634 | draft, not verified in-game |
| 0x471020 | GUESS lifted 0x471020 | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x472280 | GUESS rebind object of entity | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x472ae0 | zlnkwhands_command | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x473a70 | GUESS lifted 0x473a70 | calling convention / missing this | ec21164 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x474eb0 | GUESS transform basis through register helpers | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x474f60 | GUESS lifted 0x474f60 | calling convention / missing this | ec21164 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x476100 | GUESS lifted 0x476100 | calling convention / missing this | ec21164 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x476720 | GUESS lifted 0x476720 | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; shadow replay exact; in-game acceptance |
| 0x477a30 | GUESS lifted 0x477a30 | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x478780 | GUESS hand 0x478780 | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x47a620 | ZActor::OnSound | iterator local too small | ae0dc1f | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x47c690 | GUESS lifted 0x47c690 | slot arity / pending pushes | c6ebf84 | draft, not verified in-game |
| 0x480a40 | GUESS lifted 0x480a40 | slot arity / pending pushes | 2fb7d9d | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x481800 | (GUESS) 0x481800 two-branch sub-object update | slot arity / pending pushes | a206c44 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x482b80 | GUESS lifted 0x482b80 | calling convention / missing this | ae0dc1f | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x4831d0 | toggle_pending_lookup | slot arity / pending pushes | a206c44 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x483570 | GUESS engine word lookup then slot 0x128 | slot arity / pending pushes | 429df5f | draft, not verified in-game |
| 0x484ff0 | GUESS build vector and hand to slot | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x486900 | GUESS init timed object via slots and table id | slot arity / pending pushes | ac2c339 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x4870c0 | GUESS table lookup 114 then child vcall 128 | slot arity / pending pushes | ac2c339 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x487490 | GUESS register two ids with the engine | slot arity / pending pushes | 82b0634 | draft, not verified in-game |
| 0x48a880 | GUESS lifted 0x48a880 | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x48c6c0 | GUESS hand 0x48c6c0 | slot arity / pending pushes | 2fb7d9d | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x48f5e0 | GUESS lifted 0x48f5e0 | slot arity / pending pushes | b5a17b9 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x48ffd0 | GUESS famM 0x48ffd0 | calling convention / missing this | ac2c339 | not verified |
| 0x4903b0 | GUESS famM 0x4903b0 | calling convention / missing this | ac2c339 | not verified |
| 0x490470 | ZEngineDataBase::GetGeomFilesSize | calling convention / missing this | ac2c339 | not verified |
| 0x490500 | GUESS famM 0x490500 | calling convention / missing this | ac2c339 | not verified |
| 0x4905c0 | GUESS famH 0x4905c0 | calling convention / missing this | ac2c339 | not verified |
| 0x490650 | GUESS famK 0x490650 | calling convention / missing this | ac2c339 | not verified |
| 0x4906f0 | FUN_004906f0 (cache file size 0x68d83c) | calling convention / missing this | ac2c339 | not verified |
| 0x490790 | GUESS famK 0x490790 | calling convention / missing this | ac2c339 | not verified |
| 0x490830 | FUN_00490830 (cache file size 0x68d840) | calling convention / missing this | ac2c339 | not verified |
| 0x490a00 | GUESS famH 0x490a00 | calling convention / missing this | ac2c339 | not verified |
| 0x490b30 | GUESS famH 0x490b30 | calling convention / missing this | ac2c339 | not verified |
| 0x490c60 | ZEngineDataBase::GetRoomInsideTreeSize thiscall | calling convention / missing this | ac2c339 | not verified |
| 0x490d20 | ZEngineDataBase::GetSoundData | calling convention / missing this | ac2c339 | not verified |
| 0x490de0 | ZEngineDataBase::GetSoundDataSize | calling convention / missing this | ac2c339 | not verified |
| 0x490e70 | ZEngineDataBase::GetSoundGraphData | calling convention / missing this | ac2c339 | not verified |
| 0x490f10 | GUESS famH 0x490f10 | calling convention / missing this | ac2c339 | not verified |
| 0x490ff0 | GUESS famM 0x490ff0 | calling convention / missing this | ac2c339 | not verified |
| 0x4912a0 | ZEngineDataBase::GetTreesData thiscall | calling convention / missing this | ac2c339 | not verified |
| 0x4913d0 | GUESS famK 0x4913d0 | calling convention / missing this | ac2c339 | not verified |
| 0x491500 | GUESS famK 0x491500 | calling convention / missing this | ac2c339 | not verified |
| 0x4915a0 | GUESS famH 0x4915a0 | calling convention / missing this | ac2c339 | not verified |
| 0x49d2f0 | GUESS lifted 0x49d2f0 | calling convention / missing this | faec454 | in-game acceptance |
| 0x49f0a0 | CMsgForwardToActors::Command(unsigned short | iterator local too small | ae0dc1f | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x4a07c0 | CAction::FindAction | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x4a1190 | GUESS reset widget: register name | slot arity / pending pushes | fab35c0 | draft, not verified in-game |
| 0x4a3d60 | ZSoundAmbient::CanPlayInRoom (GUESS) thiscall | iterator local too small | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x4a47b0 | ZVertAnim::~ZVertAnim() (unknown) thiscall | sized delete | 2ac1684 | pilot n=1000 both seeds; in-game acceptance |
| 0x4a6310 | ZGeomParticle::~ZGeomParticle() (unknown) thiscall | sized delete | 2ac1684 | pilot n=1000 both seeds; in-game acceptance |
| 0x4a8f20 | GUESS initialize_registered_controls | slot arity / pending pushes | 429df5f | draft, not verified in-game |
| 0x4abc30 | CInventory::Command | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x4ac310 | GUESS apply_names | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x4ac460 | GUESS register records for listed objects | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x4ac9d0 | GUESS FUN_4ac9d0 (ZPlayer-area dispatch; name from the residue-13 list | slot arity / pending pushes | 429df5f | draft, not verified in-game |
| 0x4acf30 | GUESS lifted 0x4acf30 | slot arity / pending pushes | 2fb7d9d | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x4ad3a0 | GUESS activate_listed_objects | iterator local too small | 54ff0c4 ec21164 ae0dc1f | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x4ad4d0 | GUESS lifted 0x4ad4d0 | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x4af5b0 | GUESS scan objects toggle state | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x4b3270 | GUESS release per-frame state | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x4b3a70 | GUESS event release | iterator local too small | ac2c339 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x4b4040 | GUESS release_keys | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x4b5500 | GUESS match names or dispatch | slot arity / pending pushes | a206c44 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x4b8bb0 | ZAttachGeomToBone::Detach (unknown) thiscall | slot arity / pending pushes | 429df5f | draft, not verified in-game |
| 0x4bb380 | ZSoundToggle::~ZSoundToggle() (unknown) thiscall | sized delete | 2ac1684 | pilot n=1000 both seeds; in-game acceptance |
| 0x4bb6b0 | unnamed 0x4bb6b0 | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x4bb7c0 | GUESS advance two cursors and submit table handle | slot arity / pending pushes | fab35c0 | draft, not verified in-game |
| 0x4bbc40 | CActorCollision::~CActorCollision() (unknown) thiscall | sized delete | 2ac1684 | pilot n=1000 both seeds; in-game acceptance |
| 0x4bc250 | ZSoundRandomVolume::~ZSoundRandomVolume() (unknown) thiscall | sized delete | 2ac1684 | pilot n=1000 both seeds; in-game acceptance |
| 0x4bcd70 | ZSoundVolumetricSource::~ZSoundVolumetricSource() (unknown) thiscall | sized delete | 2ac1684 | pilot n=1000 both seeds; in-game acceptance |
| 0x4bd330 | ZSoundVolumeList::~ZSoundVolumeList() (unknown) thiscall | sized delete | 2ac1684 | pilot n=1000 both seeds; in-game acceptance |
| 0x4bd8f0 | ZSoundPitchList::~ZSoundPitchList() (unknown) thiscall | sized delete | 2ac1684 | pilot n=1000 both seeds; in-game acceptance |
| 0x4be460 | ZSoundSegment::~ZSoundSegment() (unknown) thiscall | sized delete | 2ac1684 | pilot n=1000 both seeds; in-game acceptance |
| 0x4be5e0 | ZSoundSpline::~ZSoundSpline() (unknown) thiscall | sized delete | 2ac1684 | pilot n=1000 both seeds; in-game acceptance |
| 0x4c3d30 | GUESS lifted 0x4c3d30 | slot arity / pending pushes | b5a17b9 | spec corrected, n=1000 both seeds; shadow replay exact; in-game acceptance |
| 0x4c5530 | ZPathfinderControl::CopyData(ZEventBase*) | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x4c5820 | ZMarkTextureObjGroup::Init thiscall | slot arity / pending pushes | 1163617 | draft, not verified in-game |
| 0x4c7330 | GUESS lifted 0x4c7330 | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x4c7bb0 | GUESS look up a linked object and notify it | slot arity / pending pushes | 82b0634 | draft, not verified in-game |
| 0x4c90a0 | GUESS lifted 0x4c90a0 | slot arity / pending pushes | c6ebf84 | draft, not verified in-game |
| 0x4ca820 | ZSetZDefine::Init thiscall | slot arity / pending pushes | a206c44 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x4cd470 | unnamed C-set 0x4cd470 thiscall | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x4cd880 | linkNodeInsert (GUESS) | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x4cdcc0 | GUESS release all table entries and mark object | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x4cde20 | unnamed C-set 0x4cde20 thiscall | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x4cdf70 | unnamed C-set 0x4cdf70 thiscall | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x4ce0c0 | unnamed C-set 0x4ce0c0 thiscall | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x4ce550 | GUESS iterate with out local | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x4ce5f0 | walkCount (GUESS) | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x4ce6a0 | unnamed 0x4ce6a0 | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x4ce870 | GUESS iterate set and allocate next id | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; shadow replay exact; in-game acceptance |
| 0x4cf940 | GUESS pool initialization | slot arity / pending pushes | a206c44 | in-game acceptance |
| 0x4d2bc0 | unnamed C-set 0x4d2bc0 thiscall | other (wrong return value) | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x4d3200 | GUESS hand 0x4d3200 | iterator local too small | ac2c339 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x4d39c0 | unnamed C-set 0x4d39c0 thiscall | calling convention / missing this | ae0dc1f | in-game acceptance |
| 0x4d3ab0 | unnamed C-set 0x4d3ab0 thiscall | calling convention / missing this | ae0dc1f | not verified |
| 0x4d3db0 | unnamed C-set 0x4d3db0 thiscall | calling convention / missing this | ae0dc1f | not verified |
| 0x4d5120 | IOFSMemoryAccess_t::nativeEof (high) thiscall | u32 return (bool upper bits) | 858debe | pilot n=1000 both seeds; shadow replay exact; in-game acceptance |
| 0x4d6880 | GUESS initialize and release list entries | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x4dd0c0 | GUESS FUN_4dd0c0 | slot arity / pending pushes | ac2c339 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x4e54c0 | GUESS lifted 0x4e54c0 | calling convention / missing this | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x4e6ce0 | GUESS hand 0x4e6ce0 | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; shadow replay exact; in-game acceptance |
| 0x4ec660 | strip output callback (guessed) | other (missing logic) | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x4f9c00 | GUESS lookup then vcall 310 with junk args | slot arity / pending pushes | a825738 | spec corrected, n=1000 both seeds; shadow replay exact |
| 0x4fa390 | GUESS lifted 0x4fa390 | slot arity / pending pushes | ac2c339 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x4fc500 | GUESS rebind_selected | slot arity / pending pushes | fab35c0 | draft, not verified in-game |
| 0x4fe9e0 | GUESS lifted 0x4fe9e0 | slot arity / pending pushes | c6ebf84 | draft, not verified in-game |
| 0x4fefe0 | GUESS lifted 0x4fefe0 | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x502a00 | GUESS typed value to text send | slot arity / pending pushes | 82b0634 | draft, not verified in-game |
| 0x502ba0 | GUESS resolve resource and register expression | slot arity / pending pushes | a206c44 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x502cc0 | unnamed 0x502cc0 | slot arity / pending pushes | a206c44 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x502e30 | GUESS typed value to a callback (2) | slot arity / pending pushes | 82b0634 | draft, not verified in-game |
| 0x502fe0 | GUESS resolve an id and three values then forward a handle | slot arity / pending pushes | 82b0634 | draft, not verified in-game |
| 0x503200 | dispatch503200 (GUESS) | slot arity / pending pushes | 429df5f | draft, not verified in-game |
| 0x503330 | GUESS script five-word dispatch | slot arity / pending pushes | a206c44 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x505510 | GUESS hand 0x505510 | calling convention / missing this | 2fb7d9d | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x506e80 |  | calling convention / missing this | ae0dc1f | in-game acceptance |
| 0x507e50 | unnamed 0x507e50 | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x50bef0 | GUESS obtain resource id and dispatch operation | slot arity / pending pushes | ac2c339 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x50c900 | GUESS hand 0x50c900 | calling convention / missing this | 2fb7d9d | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x50dfa0 | GUESS find entry by name then update node | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x50f9f0 | GUESS resolve handle and push value | slot arity / pending pushes | a206c44 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x512940 | create_object_chain | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x512fa0 | GUESS 0x512fa0 record loop | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x516f40 | GUESS copy vector and normalise | x87 precision | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x5194c0 | ZMoveOnSplineIf::FindSplineVal (unknown) thiscall | other (missing logic) | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x52d380 | GUESS write record kind 3 | u32 return (bool upper bits) | 858debe | pilot n=1000 both seeds; in-game acceptance |
| 0x52d4a0 | GUESS write record kind 2 | u32 return (bool upper bits) | 858debe | pilot n=1000 both seeds; in-game acceptance |
| 0x52d510 | GUESS write record kind 1 | u32 return (bool upper bits) | 858debe | pilot n=1000 both seeds; in-game acceptance |
| 0x535300 | GUESS drain_key_list | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x5355a0 | GUESS emit command records | iterator local too small | ac2c339 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x53aae0 | GUESS FUN_53aae0 | iterator local too small | ac2c339 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x53ac90 | GUESS lifted 0x53ac90 | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x53b8d0 | GUESS slot-record list builder | iterator local too small | ac2c339 | spec corrected, n=1000 both seeds |
| 0x553690 | GUESS apply_ui_state | slot arity / pending pushes | fab35c0 | draft, not verified in-game |
| 0x553980 | GUESS apply configured resource word and record output | slot arity / pending pushes | fab35c0 | draft, not verified in-game |
| 0x554bf0 | GUESS bind record to engine id (B) | slot arity / pending pushes | 799c9fa | shadow replay exact; in-game acceptance |
| 0x555e80 | FUN_00555e80 bind named object (0x6a5c48) slot 0x128 | slot arity / pending pushes | 429df5f | draft, not verified in-game |
| 0x555f20 | GUESS apply configured resource word and store presence flag | slot arity / pending pushes | fab35c0 | draft, not verified in-game |
| 0x5588e0 | classify actor up direction | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x55c5b0 | list-entry branches | slot arity / pending pushes | a206c44 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x5625c0 | path5625 (GUESS) | slot arity / pending pushes | ac2c339 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x562c90 | request_with_lookup | slot arity / pending pushes | ac2c339 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x5630f0 | callSlot84Reset (GUESS) | slot arity / pending pushes | ac2c339 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x563110 | GUESS lifted 0x563110 | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x563620 | unnamed 0x563620 | slot arity / pending pushes | a825738 | spec corrected, n=1000 both seeds; shadow replay exact; in-game acceptance |
| 0x565a30 | frame_jump_57f350 | jmp forwarder as call | ac2c339 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x565ab0 | GUESS resolve resource item and set initialized flag | slot arity / pending pushes | fab35c0 | draft, not verified in-game |
| 0x568900 | GUESS initialize UI widget handles | slot arity / pending pushes | 429df5f | draft, not verified in-game |
| 0x568dc0 | GUESS refresh pending UI list | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x56a140 | reset_ui_state | slot arity / pending pushes | c6ebf84 | draft, not verified in-game |
| 0x56a220 | GUESS UI widget command dispatcher | slot arity / pending pushes | ac2c339 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x56c1a0 | menu_command | slot arity / pending pushes | c6ebf84 | draft, not verified in-game |
| 0x56cd90 | GUESS initialise panel and register resources | slot arity / pending pushes | fab35c0 | draft, not verified in-game |
| 0x56cef0 | state_request | slot arity / pending pushes | c6ebf84 | draft, not verified in-game |
| 0x56df60 | CMultiplayerStat::OnWindowOpen | slot arity / pending pushes | 82b0634 | draft, not verified in-game |
| 0x56e050 | score_board | slot arity / pending pushes | c6ebf84 | draft, not verified in-game |
| 0x5708a0 | GUESS publish table value under one of two names | slot arity / pending pushes | fab35c0 | draft, not verified in-game |
| 0x572be0 | ui_state_push | slot arity / pending pushes | c6ebf84 | draft, not verified in-game |
| 0x574bc0 | GUESS query engine values and apply them D | slot arity / pending pushes | a206c44 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x575160 | GUESS name compare then log call | slot arity / pending pushes | 82b0634 | draft, not verified in-game |
| 0x575800 | GUESS lookup an entry and send two lines | slot arity / pending pushes | f5c98c1 | shadow replay exact; in-game acceptance |
| 0x576260 | ZSubZoneMap::Init thiscall | slot arity / pending pushes | 82b0634 | draft, not verified in-game |
| 0x5769c0 | GUESS table lookup then vcall 12c and 2f8 | slot arity / pending pushes | ac2c339 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x576a30 | node_placement | calling convention / missing this | f5c98c1 | shadow replay exact; in-game acceptance |
| 0x576e50 | GUESS lifted 0x576e50 | calling convention / missing this | ec21164 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x577d00 | ZObjectives::Init2 | slot arity / pending pushes | 429df5f | draft, not verified in-game |
| 0x5797e0 | GUESS handle mode k by resource word or helper | slot arity / pending pushes | fab35c0 | draft, not verified in-game |
| 0x57b0d0 | option_change | slot arity / pending pushes | c6ebf84 | draft, not verified in-game |
| 0x57d500 | GUESS hand 0x57d500 | slot arity / pending pushes | 2fb7d9d | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x57db50 | GUESS lifted 0x57db50 | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x57e4f0 | GUESS hand 0x57e4f0 | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x57f350 | sub_57f350 | jmp forwarder as call | ac2c339 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x582880 | CExplodeMolotov::CreateParticles (unknown) thiscall | calling convention / missing this | ae0dc1f | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x5833e0 | area_emit | other (frame fill) | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x584580 | hitpointInit (GUESS) | calling convention / missing this | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x58c150 | GUESS apply_pair | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x58d000 | GUESS lifted 0x58d000 | slot arity / pending pushes | ae0dc1f | pilot n/a (spec data file missing) |
| 0x58df40 | GUESS lifted 0x58df40 | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x58eb50 | GUESS attach_entity | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x58ecd0 | GUESS lifted 0x58ecd0 | other (frame fill) | ae0dc1f | pilot n/a (spec data file missing) |
| 0x591bb0 | GUESS_camera_focal_point | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x5922c0 | callIfOk (GUESS) | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x592410 | GUESS lifted 0x592410 | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x595570 | GUESS hand 0x595570 | calling convention / missing this | 2fb7d9d | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x597fc0 | GUESS mark option seen and show name | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x599040 | hud_controller_599040 | slot arity / pending pushes | c6ebf84 | draft, not verified in-game |
| 0x59b820 | prompt_update | slot arity / pending pushes | c6ebf84 | draft, not verified in-game |
| 0x59bd00 | ZFFLevelController::Init | slot arity / pending pushes | 429df5f | draft, not verified in-game |
| 0x59cb50 | thunk_add_5ae930 | slot arity / pending pushes | a206c44 | in-game acceptance |
| 0x59d580 | GUESS lifted 0x59d580 | calling convention / missing this | ec21164 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x59efb0 | ZFFActor::CreateItemFromItemTemplate(unsigned int) | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x59f1a0 | GUESS lifted 0x59f1a0 | calling convention / missing this | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x5a0da0 | GUESS apply selected entry | slot arity / pending pushes | a206c44 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x5a1830 | ZFFActor::OnSound | iterator local too small | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x5a1ac0 | GUESS dispatch indexed entry | calling convention / missing this | b5a17b9 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x5a86c0 | GUESS lifted 0x5a86c0 | other (frame fill) | ae0dc1f | pilot n/a (spec data file missing) |
| 0x5ab110 | kill counter +0x8b7 | calling convention / missing this | faec454 | in-game acceptance |
| 0x5af8f0 | GUESS repeat lookup and notify on entry | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x5af990 | ZFFInventoryBridge::GiveWeapon(EFFItemType | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x5afef0 | GUESS hand 0x5afef0 | iterator local too small | ac2c339 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x5b1ce0 | ZKillBox::Kill | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x5b22a0 | engine_slot_chain_5b22a0 | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x5b6d00 | GUESS lifted 0x5b6d00 | slot arity / pending pushes | c6ebf84 | draft, not verified in-game |
| 0x5b8020 | CCheckInsideBox::DoCheck (unknown) thiscall | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x5b87f0 | GUESS timer advance and fire | slot arity / pending pushes | ac2c339 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x5b8d80 | GUESS lifted 0x5b8d80 | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x5b9d50 | ZFFCareTaker_C01A::Command | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x5bb520 | ZFFCareTaker_C02A::Init2 | iterator local too small | 54ff0c4 429df5f | pilot n=1000 both seeds; later change 429df5f is a draft |
| 0x5bbfe0 | CareTaker::CareTaker5bbfe0 (GUESS) thiscall | slot arity / pending pushes | 429df5f | draft, not verified in-game |
| 0x5bc0a0 | ZFFCareTaker_C03A::Load | slot arity / pending pushes | 429df5f | draft, not verified in-game |
| 0x5bc3e0 | ZFFCareTaker_C03B::Command | slot arity / pending pushes | 429df5f | draft, not verified in-game |
| 0x5bcc10 | ZFFCareTaker_C05A::Command | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x5bce80 | ZFFCareTaker_C05A::FrameUpdate | slot arity / pending pushes | a206c44 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x5bd070 | ZFFCareTaker_C08C::Init | slot arity / pending pushes | 429df5f | draft, not verified in-game |
| 0x5bda50 | forward_command | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x5bea10 | CCivilianPathList::Load2 (civilian path builder) | slot arity / pending pushes | 429df5f | draft, not verified in-game |
| 0x5bf340 | CCivilianPathList::SetCivilianOnPath | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x5c0fc0 | GUESS lifted 0x5c0fc0 | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x5c17c0 | GUESS init handlers from named config | calling convention / missing this | f5c98c1 | shadow replay exact; in-game acceptance |
| 0x5c1910 | FUN_5c1910 (GUESS name) | slot arity / pending pushes | 429df5f | draft, not verified in-game |
| 0x5c21e0 | GUESS switch_mode | slot arity / pending pushes | fab35c0 | draft, not verified in-game |
| 0x5c40e0 | ZRepositionCharacter::CopyData (unknown) thiscall | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x5c4290 |  | calling convention / missing this | ae0dc1f | in-game acceptance |
| 0x5c53f0 | CTargetObtained::Command (GUESS) | slot arity / pending pushes | a206c44 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x5c55a0 | conditional_slot_130 | slot arity / pending pushes | a206c44 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x5c5810 | CTargetObtained::SendNotiFyMesssageToGeomsList (unknown) thiscall | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x5c5910 | GUESS countdown reroll | slot arity / pending pushes | c6ebf84 | draft, not verified in-game |
| 0x5c6cb0 | GUESS lifted 0x5c6cb0 | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x5c6f40 | GUESS hand 0x5c6f40 | slot arity / pending pushes | c6ebf84 | draft, not verified in-game |
| 0x5c74a0 | core method 0x5c74a0 (unknown) stdcall one arg | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x5c7740 | ZFFSearchLightGroup::Save | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x5c8f10 | GUESS look up or create named resource and register it | slot arity / pending pushes | fab35c0 | draft, not verified in-game |
| 0x5c92a0 | GUESS re-resolve target and notify | slot arity / pending pushes | a206c44 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x5ca5f0 | ZFFCam::UpdateVars | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x5ce0b0 | GUESS lifted 0x5ce0b0 | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x5d28c0 | GUESS update heading vectors | other (missing logic) | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x5d57c0 | GUESS reset_object_and_release_resources_by_flags | calling convention / missing this | 84ec4d1 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x5d5b40 | reset_state_engine_lookup | slot arity / pending pushes | a206c44 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x5d6af0 | bind conditional configuration set | slot arity / pending pushes | a206c44 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x5d79f0 | GUESS resolve ids and settings | slot arity / pending pushes | 82b0634 | draft, not verified in-game |
| 0x5da700 | ZCharacterControl::Init | slot arity / pending pushes | 429df5f | draft, not verified in-game |
| 0x5daf20 | GUESS 0x5daf20 teardown | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x5db4f0 | GUESS write record and child list to stream | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x5dba60 | GUESS damage box frame timers and effect | slot arity / pending pushes | a206c44 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x5dc230 | CImpactResponse::Command | slot arity / pending pushes | a206c44 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x5dc8b0 | GUESS lifted 0x5dc8b0 | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x5df5f0 | field_init_three_args | other (wrong return value) | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x5dfaa0 | best_actor_in_front | slot arity / pending pushes | c6ebf84 | draft, not verified in-game |
| 0x5dfea0 | best_actor_in_front_b | slot arity / pending pushes | c6ebf84 | draft, not verified in-game |
| 0x5e0330 | GUESS hand a pending object over | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x5e2020 | ZFFHeroMovementCloseCombat::FrameUpdate | slot arity / pending pushes | a206c44 2fb7d9d | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x5e3220 |  | calling convention / missing this | ae0dc1f | in-game acceptance |
| 0x5e4980 | ZFFHeroMovementCloseCombat::GotControl | slot arity / pending pushes | 429df5f | draft, not verified in-game |
| 0x5e5300 | ZFFHeroMovementMachinegun::GotControl | slot arity / pending pushes | 1163617 | draft, not verified in-game |
| 0x5e6ab0 | ZFFHeroMovementMachinegun::Move | slot arity / pending pushes | 429df5f | draft, not verified in-game |
| 0x5e7290 | ZFFHeroMovementMachinegun::TerminateControl | slot arity / pending pushes | 1163617 | draft, not verified in-game |
| 0x5e75a0 | ZFFHeroMovementClimb::WantControl | iterator local too small | 54ff0c4 | pilot n=1000 both seeds; in-game acceptance |
| 0x5e8460 | ZFFHeroMovementMachinegun::WantControl | slot arity / pending pushes | 429df5f | draft, not verified in-game |
| 0x5e8d40 | ZFFHeroMovementRaiseFlag::WantControl | iterator local too small | f5c98c1 | shadow replay exact; in-game acceptance |
| 0x5eac90 | CActorActionMarker::Update | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x5eb380 | ZFFActorActionThrow Execute | slot arity / pending pushes | a206c44 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x5ecd80 | GUESS view scale setup and per-entry update | other (missing logic) | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x5f0380 | GUESS query engine values and apply them | slot arity / pending pushes | a206c44 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x5f04a0 | GUESS query engine values and apply them B | slot arity / pending pushes | a206c44 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x5f0540 | GUESS query engine values and apply them C | slot arity / pending pushes | a206c44 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x5f0cd0 | fastcall_edx_pointer_slot130 | slot arity / pending pushes | a206c44 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x5f0d30 | engine_slot_114_then_130 | slot arity / pending pushes | a206c44 f5c98c1 | spec corrected, n=1000 both seeds; shadow replay exact; in-game acceptance |
| 0x5f0ff0 | GUESS lookup vcall 130 return flag | slot arity / pending pushes | ac2c339 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x5f56f0 | runProcess lifted2 | slot arity / pending pushes | ae0dc1f | not verified |
| 0x602a60 | GUESS lifted 0x602a60 | calling convention / missing this | faec454 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x607640 | GUESS load animation keys from a stream (SEH) | slot arity / pending pushes | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x61a660 | GUESS dispatch indexed key/value records | calling convention / missing this | f5c98c1 | shadow replay exact; in-game acceptance |
| 0x621230 | GUESS lifted 0x621230 | calling convention / missing this | faec454 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x634432 | GUESS atexit machinery init | slot arity / pending pushes | faec454 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x6345bc | GUESS call encoded pointer or release | slot arity / pending pushes | faec454 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x634609 | GUESS atexit register encoded | slot arity / pending pushes | faec454 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x63b850 | addPair (GUESS) | calling convention / missing this | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x63d4a0 | GUESS FUN_63d4a0 | calling convention / missing this | ac2c339 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x63e910 | GUESS lifted 0x63e910 | calling convention / missing this | dd18eed | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x646040 | sub_646040 | other (wrong return value) | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x648890 | GUESS count_mapped_elements | other (missing logic) | ae0dc1f | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x648a40 | GUESS map_elements_to_nodes | other (missing logic) | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x64a280 | GUESS compact and submit geometry records | calling convention / missing this | ae0dc1f | spec corrected, n=1000 both seeds |
| 0x64b480 | GUESS lifted 0x64b480 | calling convention / missing this | faec454 | spec corrected, n=1000 both seeds; in-game acceptance |
| 0x64d490 | GUESS lifted 0x64d490 | calling convention / missing this | dd18eed | spec corrected, n=1000 both seeds; shadow replay exact |
