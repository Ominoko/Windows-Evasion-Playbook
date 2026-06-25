# Windows Evasion Playbook 🛡️

A comprehensive, structured collection of Windows Evasion techniques implemented in C++. This repository serves as an educational reference for Red Teamers, Penetration Testers, and Security Researchers to understand how modern adversaries bypass security controls.

## Disclaimer⚠️
All code and techniques provided in this repository are strictly for **educational purposes and authorized Red Team operations**. Do not use these techniques on systems you do not own or do not have explicit permission to test.

## Tactics Matrix

### User-Mode Hook Evasion
- [ ] API Unhooking
- [ ] Direct Syscalls
- [ ] Indirect Syscalls
- [ ] API Obfuscation

### Memory Evasion
- [ ] Reflective DLL Injection
- [ ] Process Hollowing
- [ ] Thread Hijacking
- [ ] BOF Execution

### Event Suppression
- [ ] ETW Patching
- [ ] AMSI Bypass
- [ ] Call Stack Spoofing

### Kernel-Mode Evasion
- [ ] BYOVD (Bring Your Own Vulnerable Driver)
- [ ] DKOM (Direct Kernel Object Manipulation)

## 🛠️ Environment & Compilation
- **Language:** C++ (C++17/20)
- **Compiler:** MSVC / Visual Studio 2022
- **Testing Environment:** VMware Workstation (Windows 10/11 x64)

To build a specific technique, navigate to its respective directory and compile using the provided solution files.
