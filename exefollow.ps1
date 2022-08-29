class exe {

	[string] $name;

	exe([string] $name) {
		$this.name = $name;
	}

	[void] follow() {

		mode con:cols=80 lines=10;

		do
		{
			cls;

			$process = Get-Process -ErrorAction SilentlyContinue -name $this.name;

			if ($process.Count -ge 2) {
				Stop-Process $process;
				Start-Process -FilePath $this.name -WorkingDirectory "$env:PATH_APP";
				$process = Get-Process -ErrorAction SilentlyContinue -name $this.name;
			}

			$Id          = $process.Id;
			$ProcessName = $process.ProcessName;
			$MEMORY      = [Math]::Round($process.WS / 1KB); 
			$CPU         = [Math]::Round($process.CPU, 2);
			$VM          = [Math]::Round($process.VM / 1GB);
			$NPM         = [Math]::Round($process.NPM / 1KB);
			$PM          = [Math]::Round($process.PM / 1KB);

			Write-Host "`n";
			Write-Host "`r`t______________________________________________________________";
			Write-Host "`r`tId`t| App`t| Memory`t| CPU`t| VM`t| NPM`t| PM ";
			Write-Host "`r`t______________________________________________________________";
			Write-Host "`r`t$ID`t| $ProcessName`t| $MEMORY`t`t| $CPU`t| $VM`t| $NPM`t| $PM";

			if ([Console]::KeyAvailable) {
				$key = [Console]::ReadKey($true);
				if($key.Key -eq [ConsoleKey]::Escape) {
					break;
				}
			}

			Start-Sleep -m 500; 
		} while (1);

		mode con:cols=95 lines=50;

	}
}

# >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
[exe] $exe = [exe]::new($args[0]);
$exe.follow();
# >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

