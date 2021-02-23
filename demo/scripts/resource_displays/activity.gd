extends PanelContainer


onready var state_line_edit: = $VBoxContainer/State/LineEdit
onready var details_line_edit: = $VBoxContainer/Details/LineEdit
onready var timestamps: = $VBoxContainer/Timestamps
onready var assets: = $VBoxContainer/Assets
onready var party: = $VBoxContainer/Party
onready var secrets: = $VBoxContainer/Secrets

var activity: Discord.Activity setget set_activity


func set_activity(new_activity: Discord.Activity) -> void:
	if new_activity:
		state_line_edit.text = new_activity.state
		details_line_edit.text = new_activity.details
		timestamps.timestamps = new_activity.timestamps
		assets.assets = new_activity.assets
		party.party = new_activity.party
		secrets.secrets = new_activity.secrets
