
/* WARNING: Control flow encountered bad instruction data */

void entry(void)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  byte local_258[520];
  byte local_50[8];
  byte local_48[8];
  uint local_40;
  uint local_3c;
  int local_38;
  int local_34;
  uint local_30;
  uint local_2c;
  uint local_28;
  uint local_24;
  int local_20;
  int local_1c;
  uint local_18;
  uint local_14;
  uint local_10;
  byte local_c;
  byte local_b;
  byte local_a;
  char local_9;

  local_3c = 0xe;
  local_40 = 0x3bf7b3e8;
  while (true)
  {
    while (true)
    {
      while (true)
      {
        while (true)
        {
          while (true)
          {
            while (true)
            {
              while (true)
              {
                while (true)
                {
                  while (true)
                  {
                    while (true)
                    {
                      while (true)
                      {
                        while (true)
                        {
                          while (true)
                          {
                            while (true)
                            {
                              while (true)
                              {
                                while (true)
                                {
                                  while (true)
                                  {
                                    while (true)
                                    {
                                      while (true)
                                      {
                                        while (true)
                                        {
                                          while (true)
                                          {
                                            while (true)
                                            {
                                              while (true)
                                              {
                                                while (true)
                                                {
                                                  while (true)
                                                  {
                                                    while (true)
                                                    {
                                                      while (true)
                                                      {
                                                        while (true)
                                                        {
                                                          while (true)
                                                          {
                                                            while (true)
                                                            {
                                                              while (true)
                                                              {
                                                                while (true)
                                                                {
                                                                  while (true)
                                                                  {
                                                                    while (true)
                                                                    {
                                                                      while (true)
                                                                      {
                                                                        while (true)
                                                                        {
                                                                          while (true)
                                                                          {
                                                                            while (true)
                                                                            {
                                                                              while (true)
                                                                              {
                                                                                while (true)
                                                                                {
                                                                                  while (true)
                                                                                  {
                                                                                    while (true)
                                                                                    {
                                                                                      while (true)
                                                                                      {
                                                                                        while (true)
                                                                                        {
                                                                                          while (local_40 == 0xfd43debe)
                                                                                          {
                                                                                            local_34 = local_34 + 1;
                                                                                            local_3c = local_3c ^ 0x18;
                                                                                            local_40 = 0x3bf7b3e8;
                                                                                          }
                                                                                          if (0xfd43debe < local_40)
                                                                                            goto LAB_00402021;
                                                                                          if (local_40 != 0xfabbeeff)
                                                                                            break;
                                                                                          local_48[(ulong)local_10] = 0;
                                                                                          local_3c = local_3c ^ 0x33;
                                                                                          local_40 = 0x3bf7b3e8;
                                                                                        }
                                                                                        if (0xfabbeeff < local_40)
                                                                                          goto LAB_00402021;
                                                                                        if (local_40 != 0xf7d93037)
                                                                                          break;
                                                                                        if (local_10 < 8)
                                                                                        {
                                                                                          uVar5 = FUN_004012cd((ulong)(local_3c ^ 0x401144), 0x401f76, 0x401f7d);
                                                                                          local_3c = local_3c ^ uVar5 ^ 0xc;
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                          local_3c = local_3c ^ 0x2b;
                                                                                        }
                                                                                        local_40 = 0x3bf7b3e8;
                                                                                      }
                                                                                      if (0xf7d93037 < local_40)
                                                                                        goto LAB_00402021;
                                                                                      if (local_40 != 0xf0210076)
                                                                                        break;
                                                                                      iVar3 = local_38 + local_34 * 0x40;
                                                                                      if (iVar3 < 0)
                                                                                      {
                                                                                        iVar3 = iVar3 + 7;
                                                                                      }
                                                                                      iVar2 = local_38 + local_34 * 0x40;
                                                                                      bVar1 = (byte)(iVar2 >> 0x37);
                                                                                      iVar4 = local_38 + local_34 * 0x40;
                                                                                      if (iVar4 < 0)
                                                                                      {
                                                                                        iVar4 = iVar4 + 7;
                                                                                      }
                                                                                      local_258[(long)(iVar4 >> 3)] =
                                                                                          local_258[(long)(iVar3 >> 3)] ^
                                                                                          (byte)(1 << (((char)iVar2 + (bVar1 >> 5) & 7) - (bVar1 >> 5) & 0x1f));
                                                                                      local_3c = local_3c ^ 0x2e;
                                                                                      local_40 = 0x3bf7b3e8;
                                                                                    }
                                                                                    if (0xf0210076 < local_40)
                                                                                      goto LAB_00402021;
                                                                                    if (local_40 != 0xead8e086)
                                                                                      break;
                                                                                    local_24 = local_30 + local_2c;
                                                                                    local_28 = (local_30 >> 6 | local_30 << 0x1a) ^
                                                                                               local_24;
                                                                                    local_40 = 0x477279ad;
                                                                                  }
                                                                                  if (0xead8e086 < local_40)
                                                                                    goto LAB_00402021;
                                                                                  if (local_40 != 0xe07bc905)
                                                                                    break;
                                                                                  iVar3 = local_34;
                                                                                  if (local_34 < 0)
                                                                                  {
                                                                                    iVar3 = local_34 + 7;
                                                                                  }
                                                                                  iVar4 = local_38;
                                                                                  if (local_38 < 0)
                                                                                  {
                                                                                    iVar4 = local_38 + 7;
                                                                                  }
                                                                                  if ((iVar3 >> 3) - (iVar4 >> 3) < 0)
                                                                                  {
                                                                                    local_3c = local_3c ^ 0x32;
                                                                                  }
                                                                                  else
                                                                                  {
                                                                                    local_3c = local_3c ^ 0x24;
                                                                                  }
                                                                                  local_40 = 0x3bf7b3e8;
                                                                                }
                                                                                if (0xe07bc905 < local_40)
                                                                                  goto LAB_00402021;
                                                                                if (local_40 != 0xd385ae96)
                                                                                  break;
                                                                                if (local_34 < 0x40)
                                                                                {
                                                                                  local_3c = local_3c ^ 0x17;
                                                                                }
                                                                                else
                                                                                {
                                                                                  local_3c = local_3c ^ 0xf;
                                                                                }
                                                                                local_40 = 0x3bf7b3e8;
                                                                              }
                                                                              if (0xd385ae96 < local_40)
                                                                                goto LAB_00402021;
                                                                              uVar5 = local_34 >> 0x1f;
                                                                              uVar6 = local_38 >> 0x1f;
                                                                              if (local_40 != 0xcc7c1ed7)
                                                                                break;
                                                                              if ((int)(((local_34 + (uVar5 >> 0x1d) & 7) -
                                                                                         (uVar5 >> 0x1d)) -
                                                                                        ((local_38 + (uVar6 >> 0x1d) & 7) -
                                                                                         (uVar6 >> 0x1d))) < 0)
                                                                              {
                                                                                local_3c = local_3c ^ 0x20;
                                                                              }
                                                                              else
                                                                              {
                                                                                local_3c = local_3c ^ 7;
                                                                              }
                                                                              local_40 = 0x3bf7b3e8;
                                                                            }
                                                                            if (0xcc7c1ed7 < local_40)
                                                                              goto LAB_00402021;
                                                                            if (local_40 != 0xc96691ce)
                                                                              break;
                                                                            iVar3 = local_38;
                                                                            if (local_38 < 0)
                                                                            {
                                                                              iVar3 = local_38 + 7;
                                                                            }
                                                                            bVar1 = (byte)(local_38 >> 0x37);
                                                                            local_a = (byte)((int)(uint)local_48[(long)(iVar3 >> 3)] >> (((char)local_38 + (bVar1 >> 5) & 7) -
                                                                                                                                             (bVar1 >> 5) &
                                                                                                                                         0x1f)) &
                                                                                      1;
                                                                            local_3c = local_3c ^ 5;
                                                                            local_40 = 0x3bf7b3e8;
                                                                          }
                                                                          if (0xc96691ce < local_40)
                                                                            goto LAB_00402021;
                                                                          bVar1 = (byte)(local_34 >> 0x37);
                                                                          if (local_40 != 0xc6bcbeed)
                                                                            break;
                                                                          iVar3 = local_34;
                                                                          if (local_34 < 0)
                                                                          {
                                                                            iVar3 = local_34 + 7;
                                                                          }
                                                                          iVar4 = local_34;
                                                                          if (local_34 < 0)
                                                                          {
                                                                            iVar4 = local_34 + 7;
                                                                          }
                                                                          local_50[(long)(iVar4 >> 3)] =
                                                                              local_50[(long)(iVar3 >> 3)] ^
                                                                              (byte)(((uint)local_c & 1) << (((char)local_34 + (bVar1 >> 5) & 7) -
                                                                                                                 (bVar1 >> 5) &
                                                                                                             0x1f));
                                                                          local_3c = local_3c ^ 0x23;
                                                                          local_40 = 0x3bf7b3e8;
                                                                        }
                                                                        if (0xc6bcbeed < local_40)
                                                                          goto LAB_00402021;
                                                                        if (local_40 != 0xc2e652f6)
                                                                          break;
                                                                        if (local_14 < 8)
                                                                        {
                                                                          local_3c = local_3c ^ 0x39;
                                                                        }
                                                                        else
                                                                        {
                                                                          local_3c = local_3c ^ 0xd;
                                                                        }
                                                                        local_40 = 0x3bf7b3e8;
                                                                      }
                                                                      if (0xc2e652f6 < local_40)
                                                                        goto LAB_00402021;
                                                                      if (local_40 != 0xb938593d)
                                                                        break;
                                                                      iVar3 = local_34;
                                                                      if (local_34 < 0)
                                                                      {
                                                                        iVar3 = local_34 + 7;
                                                                      }
                                                                      local_9 = local_9 + ((byte)((int)(uint)local_50[(
                                                                                                      long)(iVar3 >> 3)] >>
                                                                                                  (((char)local_34 + (bVar1 >> 5) & 7) -
                                                                                                       (bVar1 >> 5) &
                                                                                                   0x1f)) &
                                                                                           1);
                                                                      local_3c = local_3c ^ 0xf;
                                                                      local_40 = 0x3bf7b3e8;
                                                                    }
                                                                    if (0xb938593d < local_40)
                                                                      goto LAB_00402021;
                                                                    if (local_40 != 0xb36536b6)
                                                                      break;
                                                                    local_50[0] = 0xff;
                                                                    local_3c = local_3c ^ 0x18;
                                                                    local_40 = 0x3bf7b3e8;
                                                                  }
                                                                  if (0xb36536b6 < local_40)
                                                                    goto LAB_00402021;
                                                                  if (local_40 != 0xa9a5e827)
                                                                    break;
                                                                  local_38 = local_38 + 1;
                                                                  local_3c = local_3c ^ 0x35;
                                                                  local_40 = 0x3bf7b3e8;
                                                                }
                                                                if (0xa9a5e827 < local_40)
                                                                  goto LAB_00402021;
                                                                if (local_40 != 0xa745fea6)
                                                                  break;
                                                                local_38 = local_38 + 1;
                                                                local_3c = local_3c ^ 0x16;
                                                                local_40 = 0x3bf7b3e8;
                                                              }
                                                              if (0xa745fea6 < local_40)
                                                                goto LAB_00402021;
                                                              if (local_40 != 0xa4014946)
                                                                break;
                                                              local_18 = 1;
                                                              local_3c = local_3c ^ 10;
                                                              local_40 = 0x3bf7b3e8;
                                                            }
                                                            if (0xa4014946 < local_40)
                                                              goto LAB_00402021;
                                                            if (local_40 != 0xa3f97907)
                                                              break;
                                                            if (local_38 < 0x40)
                                                            {
                                                              local_3c = local_3c ^ 0x2d;
                                                            }
                                                            else
                                                            {
                                                              local_3c = local_3c ^ 0x18;
                                                            }
                                                            local_40 = 0x3bf7b3e8;
                                                          }
                                                          if (0xa3f97907 < local_40)
                                                            goto LAB_00402021;
                                                          if (local_40 != 0x9ffd26c4)
                                                            break;
                                                          local_34 = 0;
                                                          local_3c = local_3c ^ 1;
                                                          local_40 = 0x3bf7b3e8;
                                                        }
                                                        if (0x9ffd26c4 < local_40)
                                                          goto LAB_00402021;
                                                        if (local_40 != 0x9c1df858)
                                                          break;
                                                        local_c = local_a & local_b;
                                                        local_3c = local_3c ^ 0x2c;
                                                        local_40 = 0x3bf7b3e8;
                                                      }
                                                      if (0x9c1df858 < local_40)
                                                        goto LAB_00402021;
                                                      if (local_40 != 0x9bda85b9)
                                                        break;
                                                      local_258[0] = 0;
                                                      local_3c = local_3c ^ 0x13;
                                                      local_40 = 0x3bf7b3e8;
                                                    }
                                                    if (0x9bda85b9 < local_40)
                                                      goto LAB_00402021;
                                                    if (local_40 != 0x96e67d8f)
                                                      break;
                                                    if (local_38 < 0x40)
                                                    {
                                                      local_3c = local_3c ^ 0x33;
                                                    }
                                                    else
                                                    {
                                                      local_3c = local_3c ^ 0x1c;
                                                    }
                                                    local_40 = 0x3bf7b3e8;
                                                  }
                                                  if (0x96e67d8f < local_40)
                                                    goto LAB_00402021;
                                                  if (local_40 != 0x93a5489f)
                                                    break;
                                                  local_14 = 1;
                                                  local_3c = local_3c ^ 0x28;
                                                  local_40 = 0x3bf7b3e8;
                                                }
                                                if (0x93a5489f < local_40)
                                                  goto LAB_00402021;
                                                if (local_40 != 0x911e4dce)
                                                  break;
                                                iVar3 = local_38;
                                                if (local_38 < 0)
                                                {
                                                  iVar3 = local_38 + 7;
                                                }
                                                iVar4 = local_34;
                                                if (local_34 < 0)
                                                {
                                                  iVar4 = local_34 + 7;
                                                }
                                                local_1c = (iVar3 >> 3) - (iVar4 >> 3);
                                                local_3c = local_3c ^ 0x2c;
                                                local_40 = 0x3bf7b3e8;
                                              }
                                              if (0x911e4dce < local_40)
                                                goto LAB_00402021;
                                              if (local_40 != 0x853f06be)
                                                break;
                                              local_38 = 0;
                                              local_3c = local_3c ^ 0x38;
                                              local_40 = 0x3bf7b3e8;
                                            }
                                            if (0x853f06be < local_40)
                                              goto LAB_00402021;
                                            if (local_40 != 0x82c736ff)
                                              break;
                                            if ((uint)(local_20 + local_1c) < 2)
                                            {
                                              local_3c = local_3c ^ 0x3c;
                                            }
                                            else
                                            {
                                              local_3c = local_3c ^ 0x12;
                                            }
                                            local_40 = 0x3bf7b3e8;
                                          }
                                          if (0x82c736ff < local_40)
                                            goto LAB_00402021;
                                          if (local_40 != 0x7d85a117)
                                            break;
                                          local_18 = local_18 + 1;
                                          local_3c = local_3c ^ 0x3a;
                                          local_40 = 0x3bf7b3e8;
                                        }
                                        if (0x7d85a117 < local_40)
                                          goto LAB_00402021;
                                        if (local_40 != 0x78c71567)
                                          break;
                                        local_10 = local_10 + 1;
                                        local_3c = local_3c ^ 0x3f;
                                        local_40 = 0x3bf7b3e8;
                                      }
                                      if (0x78c71567 < local_40)
                                        goto LAB_00402021;
                                      if (local_40 != 0x6e9ca60f)
                                        break;
                                      if (local_34 < 0x40)
                                      {
                                        local_3c = local_3c ^ 0x18;
                                      }
                                      else
                                      {
                                        local_3c = local_3c ^ 0x32;
                                      }
                                      local_40 = 0x3bf7b3e8;
                                    }
                                    if (0x6e9ca60f < local_40)
                                      goto LAB_00402021;
                                    if (local_40 != 0x6ce7dd77)
                                      break;
                                    if (local_34 < 0x40)
                                    {
                                      local_3c = local_3c ^ 7;
                                    }
                                    else
                                    {
                                      local_3c = local_3c ^ 0x18;
                                    }
                                    local_40 = 0x3bf7b3e8;
                                  }
                                  if (0x6ce7dd77 < local_40)
                                    goto LAB_00402021;
                                  if (local_40 != 0x6964964e)
                                    break;
                                  local_34 = 0;
                                  local_3c = local_3c ^ 1;
                                  local_40 = 0x3bf7b3e8;
                                }
                                if (0x6964964e < local_40)
                                  goto LAB_00402021;
                                if (local_40 != 0x68bcb16c)
                                  break;
                                local_34 = 0;
                                local_3c = local_3c ^ 0x27;
                                local_40 = 0x3bf7b3e8;
                              }
                              if (0x68bcb16c < local_40)
                                goto LAB_00402021;
                              if (local_40 != 0x627d9156)
                                break;
                              local_20 = ((local_38 + (uVar6 >> 0x1d) & 7) - (uVar6 >> 0x1d)) -
                                         ((local_34 + (uVar5 >> 0x1d) & 7) - (uVar5 >> 0x1d));
                              local_3c = local_3c ^ 9;
                              local_40 = 0x3bf7b3e8;
                            }
                            if (0x627d9156 < local_40)
                              goto LAB_00402021;
                            if (local_40 != 0x5d45d93e)
                              break;
                            syscall();
                            local_3c = local_3c ^ 0x24;
                            local_40 = 0x3bf7b3e8;
                          }
                          if (0x5d45d93e < local_40)
                            goto LAB_00402021;
                          if (local_40 != 0x5abde97f)
                            break;
                          iVar3 = local_38 + local_34 * 0x40;
                          if (iVar3 < 0)
                          {
                            iVar3 = iVar3 + 7;
                          }
                          iVar4 = local_38 + local_34 * 0x40;
                          bVar1 = (byte)(iVar4 >> 0x37);
                          local_b = (byte)((int)(uint)local_258[(long)(iVar3 >> 3)] >>
                                           (((char)iVar4 + (bVar1 >> 5) & 7) - (bVar1 >> 5) & 0x1f)) &
                                    local_a & 1;
                          local_3c = local_3c ^ 0x12;
                          local_40 = 0x3bf7b3e8;
                        }
                        if (0x5abde97f < local_40)
                          goto LAB_00402021;
                        if (local_40 != 0x551e5e5d)
                          break;
                        local_50[(ulong)local_14] = 0xff;
                        local_3c = local_3c ^ 0x3b;
                        local_40 = 0x3bf7b3e8;
                      }
                      if (0x551e5e5d < local_40)
                        goto LAB_00402021;
                      if (local_40 != 0x480746e6)
                        break;
                      local_34 = local_34 + 1;
                      local_3c = local_3c ^ 0x2d;
                      local_40 = 0x3bf7b3e8;
                    }
                    if (0x480746e6 < local_40)
                      goto LAB_00402021;
                    if (local_40 != 0x477279ad)
                      break;
                    local_2c = local_28 + local_24;
                    local_30 = (local_28 >> 0xd | local_28 << 0x13) ^ local_2c;
                    local_40 = 0x115bde3f;
                  }
                  if (0x477279ad < local_40)
                    goto LAB_00402021;
                  if (local_40 != 0x41ff0669)
                    break;
                  iVar3 = local_34;
                  if (local_34 < 0)
                  {
                    iVar3 = local_34 + 7;
                  }
                  iVar4 = local_38;
                  if (local_38 < 0)
                  {
                    iVar4 = local_38 + 7;
                  }
                  local_1c = (iVar3 >> 3) - (iVar4 >> 3);
                  local_3c = local_3c ^ 0x3a;
                  local_40 = 0x3bf7b3e8;
                }
                if (0x41ff0669 < local_40)
                  goto LAB_00402021;
                if (local_40 != 0x4071ce85)
                  break;
                local_258[(ulong)local_18] = 0;
                local_3c = local_3c ^ 0x1f;
                local_40 = 0x3bf7b3e8;
              }
              if (0x4071ce85 < local_40)
                goto LAB_00402021;
              if (local_40 != 0x3f1fc24f)
                break;
              local_10 = 1;
              local_3c = local_3c ^ 0x18;
              local_40 = 0x3bf7b3e8;
            }
            if (0x3f1fc24f < local_40)
              goto LAB_00402021;
            if (local_40 != 0x3da4c71e)
              break;
            local_20 = ((local_34 + (uVar5 >> 0x1d) & 7) - (uVar5 >> 0x1d)) -
                       ((local_38 + (uVar6 >> 0x1d) & 7) - (uVar6 >> 0x1d));
            local_3c = local_3c ^ 0x2e;
            local_40 = 0x3bf7b3e8;
          }
          if (0x3da4c71e < local_40)
            goto LAB_00402021;
          if (local_40 != 0x3bf7b3e8)
            break;
          local_2c = local_3c + 0x6345789;
          local_30 = (local_3c << 7 | local_3c >> 0x19) ^ local_2c;
          local_40 = 0xead8e086;
        }
        if (0x3bf7b3e8 < local_40)
          goto LAB_00402021;
        if (local_40 != 0x38e7720e)
          break;
        local_14 = local_14 + 1;
        local_3c = local_3c ^ 2;
        local_40 = 0x3bf7b3e8;
      }
      if (0x38e7720e < local_40)
        goto LAB_00402021;
      if (local_40 != 0x385c57e7)
        break;
      local_38 = 0;
      local_3c = local_3c ^ 0x29;
      local_40 = 0x3bf7b3e8;
    }
    if (0x385c57e7 < local_40)
      goto LAB_00402021;
    if (local_40 == 0x31ff2945)
      break;
    if (0x31ff2945 < local_40)
      goto LAB_00402021;
    if (local_40 == 0x2b3e893f)
    {
      local_34 = local_34 + 1;
      local_3c = local_3c ^ 0x27;
      local_40 = 0x3bf7b3e8;
    }
    else
    {
      if (0x2b3e893f < local_40)
        goto LAB_00402021;
      if (local_40 == 0x29840f0e)
      {
        local_48[0] = 0;
        local_3c = local_3c ^ 0xf;
        local_40 = 0x3bf7b3e8;
      }
      else
      {
        if (0x29840f0e < local_40)
          goto LAB_00402021;
        if (local_40 == 0x1627af6e)
        {
          local_9 = 0;
          local_3c = local_3c ^ 0x11;
          local_40 = 0x3bf7b3e8;
        }
        else
        {
          if (0x1627af6e < local_40)
            goto LAB_00402021;
          if (local_40 == 0x743f926)
          {
            if (local_18 < 0x200)
            {
              local_3c = local_3c ^ 0x25;
            }
            else
            {
              local_3c = local_3c ^ 0x22;
            }
            local_40 = 0x3bf7b3e8;
          }
          else
          {
            if (local_40 != 0x115bde3f)
              goto LAB_00402021;
            local_24 = local_30 + local_2c;
            local_40 = (local_30 << 0xb | local_30 >> 0x15) ^ local_24;
          }
        }
      }
    }
  }
  if (local_9 == 0)
  {
    FUN_00401332(local_48);
  }
  else
  {
    syscall();
  }
LAB_00402021:
  syscall();
  /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}
