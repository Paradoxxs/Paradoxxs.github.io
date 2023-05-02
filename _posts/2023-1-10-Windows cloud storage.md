The usage of cloud storage are becoming a standard when examining computers, I have tried to list the locations of where you can find evidence of cloud storage on Windows.

## OneDrive

It is critical to check the registry to confirm the local file storage location&#x20;

• Metadata files only exist if OneDrive is enabled&#x20;

• SyncDiagnostics.log can sometimes contain file metadata&#x20;

• Some files are only stored in the cloud and will not be stored locally&#x20;

• Deleted items are stored in an online recycle bin for up to 30 days (personal) or 93 days (business)&#x20;

• OneDrive for Business Unified Audit Logs in Microsoft 365 provide 90 days of user activity logging

```
%USERPROFILE%\OneDrive
```

File storage folder location

```
NTUSER\Software\Microsoft\OneDrive\Accounts\<Personal | Business1>
```

File data metadata

```
%USERPROFILE%\AppData\Local\Microsoft\OneDrive\logs\<Personal | Business1>
```

* SyncDiagnostics.log
* SyncEngine “odl” logs

```
%USERPROFILE%\AppData\Local\Microsoft\OneDrive\settings\<Personal | Business1> <UserCid>.dat
```

## Google Drive for Desktop

It uses a virtual FAT32 volume named “My Drive”, which is only accessible to the user when they are logged in.

The assigned drive letter can help tie file and folder access artefacts to Google Drive&#x20;

• Google Workspace Admin Reports provide 180 days of user activity logging&#x20;

• metadata\_sqlite\_db database uses protobuf format for many important fields

Local drive letter for the virtual volume and account ID

```
NTUSER\Software\Google\DriveFS\Share\
```

Default local file cache

```
%USERPROFILE%\AppData\Local\Google\DriveFS\<account
identifier>\content_cache
```

File metadata

```
%USERPROFILE%\AppData\Local\Google\DriveFS\<account
identifier>\metadata_sqlite_db
```

## Dropbox

Default local file storage

```
%USERPROFILE%\Dropbox
```

```
%USERPROFILE%\Dropbox\.dropbox.cache (up to 3 days of cached data)
```

File storage folder location

```
SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\SyncRootManager\Dropbox!<SID>!Personal\UserSyncRoots
```

File metadata and configuration data

```
%USERPROFILE%\AppData\Local\Dropbox\
```

* nucleus.sqlite3, sync\_history.db, and aggregation.dbx – usage and file