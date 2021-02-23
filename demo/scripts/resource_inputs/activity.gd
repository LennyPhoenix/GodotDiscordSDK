extends PanelContainer


onready var state_line_edit: = $VBoxContainer/State
onready var details_line_edit: = $VBoxContainer/Details
onready var timestamps: = $VBoxContainer/Timestamps
onready var assets: = $VBoxContainer/Assets
onready var party: = $VBoxContainer/Party
onready var secrets: = $VBoxContainer/Secrets


func get_activity() -> Discord.Activity:
	var activity: = Discord.Activity.new()
	activity.state = state_line_edit.text
	activity.details = details_line_edit.text
	activity.timestamps = timestamps.get_timestamps()
	activity.assets = assets.get_assets()
	activity.party = party.get_party()
	activity.secrets = secrets.get_secrets()
	return activity
