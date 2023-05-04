# Setup Development Hosts

For this course, we will use the following infrastructure.

|  Host        | Architecture | Location    | Notes                       |
|:-------------|:------------:|:------------|:----------------------------|
| Ubuntu-22.04 | X86_64       | Azure       | Development and Build machine. Compile code and test in this host. |
| Windows      | X86_64       | On-premises | Desktop environment. Run VSCode here and connect remotely over SSH to Linux VM in Azure |

## Setup Development and Build machine in Azure

Run the following steps on your windows desktop.

### Step 1: Login to Azure (may not be needed on your corporate windows desktop)

```
az login --use-device-code
```

#### Step 1.1: Set Azure Subscription

```
az account set --subscription <subscription uuid>
```

### Step 2: Generate SSH key pair

```shell
ssh-keygen `
    -m PEM `
    -t rsa `
    -b 4096 `
    -C "<your-user-id>@<your-user-id>-ubuntu-dev-1" `
    -f c:/users/<your-user-id>/.ssh/<your-user-id>-ubuntu-dev-1
```
Note: [Detailed notes on creating SSH keys](https://learn.microsoft.com/en-us/azure/virtual-machines/linux/create-ssh-keys-detailed)

#### Example

```
ssh-keygen `
    -m PEM `
    -t rsa `
    -b 4096 `
    -C "snambakam@snambakam-ubuntu-dev-1" `
    -f c:/users/snambakam/.ssh/snambakam-ubuntu-dev-1
```

### Step 3: Generate VM in Azure

```powershell
az vm create `
	--resource-group <your-user-id>-dev-test `
	--name <your-user-id>-ubuntu-dev-1 `
	--image Canonical:0001-com-ubuntu-server-jammy:22_04-lts:22.04.202304280 `
	--os-disk-size-gb 40 `
	--size Standard_F2s_v2 `
	--public-ip-sku Standard `
	--admin-username <your-user-id> `
	--assign-identity [system] `
	--ssh-key-values c:/users/<your-user-id>/.ssh/<your-user-id>-ubuntu-dev-1.pub `
	--location westus2
```

#### Example

```
az vm create `
	--resource-group snambakam-dev-test `
	--name snambakam-ubuntu-dev-1 `
	--image Canonical:0001-com-ubuntu-server-jammy:22_04-lts:22.04.202304280 `
	--os-disk-size-gb 40 `
	--size Standard_F2s_v2 `
	--public-ip-sku Standard `
	--admin-username snambakam `
	--assign-identity [system] `
	--ssh-key-values c:/users/snambakam/.ssh/snambakam-ubuntu-dev-1.pub `
	--location westus2
```

Note: Please note down the public IP Address from the output of this command

### Step 4: Create an SSH Config file

The file would be located at ~/.ssh/config

The contents of this file should include the following.

```powershell
Host <your-user-id>-ubuntu-dev-1
    Hostname <Public IP Address of your VM>
    User <your-user-id>
    IdentityFile <absolute path to ~/.ssh/<your-user-id>-ubuntu-dev-1>>
```

#### Example

```
Host snambakam-ubuntu-dev-1
    Hostname 10.20.130.44
    User snambakam
    IdentityFile "C:/Users/snambakam/.ssh/snambakam-ubuntu-dev-1"
```

# References

1. [Azure Portal](https://azure.microsoft.com/en-us/features/azure-portal/)
1. [Device Login Page](https://microsoft.com/devicelogin)
