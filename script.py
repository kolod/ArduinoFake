import platform
Import("env")


host_os = platform.system().lower()

print(f"Detected host OS: {host_os}")

if host_os == "windows":
    env.Append(CCFLAGS=["-Wa,-mbig-obj"])
