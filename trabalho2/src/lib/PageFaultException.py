class PageFaultException(Exception):
    def __init__(self):
        super().__init__("PageFaultException")
