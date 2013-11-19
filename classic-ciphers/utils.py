import re

def clean_data(data):
	data = data.replace('\n', '')
	data = data.replace(' ', '')
	data = data.upper()
	data = re.sub('[\W]', '', data)
	return data